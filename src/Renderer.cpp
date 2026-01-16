// Renderer.cpp
// Implementation of rendering functions
#include "Renderer.hpp"
#include "proc.hpp"
#include "Pet.hpp"
#include <cfloat>
#include <ncurses.h>
#include <algorithm>
#include <inttypes.h>



static void printBytes(int y, int x, const char* label, std::uint64_t bytes) {
    if (bytes >= (1ULL << 30)) {
        mvprintw(y, x, "%s: %.2f GiB", label, bytes / 1073741824.0);
    } else if (bytes >= (1ULL << 20)) {
        mvprintw(y, x, "%s: %.2f MiB", label, bytes / 1048576.0);
    } else {
        mvprintw(y, x, "%s: %.2f KiB", label, bytes / 1024.0);
    }
}


// ASCII art for the pet (a simple cat)
static const char* CAT_ART = R"(
 /\_/\
( o.o )
 > ^ <
)";

static const char* SAD_CAT = R"(
 /\_/\
( T.T )
 > ^
)";

static const char* ANGRY_CAT = R"(
 /\_/\
( >.< )
 > ^
)";

static const char* HUNGRY_CAT = R"(
 /\_/\
( 0.- )
 > ~ <
)";

static const char* SLEEPY_CAT = R"(
 /\_/\
( -.- )
 z  z
)";

static const char* DEAD_CAT = R"(
 /\_/\
( x.x )
  v v
)";

void Renderer::init() {
    getmaxyx(stdscr, m_height, m_width);
}

void Renderer::shutdown() {
}

void Renderer::pushEvent(std::string msg) {
    m_events.push_back(std::move(msg));

    if (m_events.size() > 50) {
        m_events.erase(m_events.begin());
    }
}

void Renderer::draw(const PetState& state) {
    getmaxyx(stdscr, m_height, m_width);

    erase();

    drawFrame();

    drawPetVisual(2, 2, state);                      // Pet in top-left
    drawStats(state, 2, 25);                  // Stats next to pet
    drawCommands(m_height - 6, 2);            // Commands at bottom-left
    drawEventLog(m_height - 25, 35, 4);        // Log at bottom-right

    mvprintw(19, 2, "CPU: %d%%", state.sMetrics.cpuPet);
    mvprintw(24, 2, "MEM: %d%%", state.sMetrics.memPet);
    printBytes(29, 2, "DISK", state.diskOut.usedBytes);
    mvprintw(32, 2, "UPTIME: %.1f s", state.uptimeOut.uptimeSeconds);

    if (state.showDebug) {
      mvprintw(14, 2, "Press 'd' to turn off debug mode.");
      // TEMP: /proc/cpu debug
      mvprintw(15, 2, "CPU Raw Info:");
      mvprintw(16, 2, "User:   %llu", state.cpuOut.user);
      mvprintw(17, 2, "System: %llu", state.cpuOut.system);
      mvprintw(18, 2, "Idle:   %llu", state.cpuOut.idle);


      // /proc/meminfo
      mvprintw(21, 2, "Memory Raw Info:");
      mvprintw(22, 2, "Total: %llu kB", state.memOut.memTotalKb);
      mvprintw(23, 2, "Available: %llu kB", state.memOut.memAvailableKb);


      // statvfs for disk spaces
      mvprintw(26, 2, "Disk Space Info:");
      printBytes(27, 2, "Total", state.diskOut.totalBytes);
      printBytes(28, 2, "Available", state.diskOut.availBytes);


      // /proc/uptime
      mvprintw(31, 2, "Uptime Info:");

    }
    refresh();
}

void Renderer::drawFrame() {
    box(stdscr, 0, 0);                        // Draws a little border around the screen
    mvprintw(0, 2, " digital-pet ");          // Creates the title in top left border
}

void Renderer::drawPetVisual(int y, int x, const PetState& state) {

    int colorPair{1};    // Default green for happy
    const char* art = CAT_ART;

    // Check death FIRST - most important state!
    if (!state.isAlive) {
        colorPair = 2; // red for dead
        art = DEAD_CAT;
    } else if (state.pStats.happiness < 30) {
        colorPair = 3; // Blue - sad.. :(
        art = SAD_CAT;
    } else if (state.pStats.energy < 40) {
        colorPair = 2;  // Red - tired or angry
        art = ANGRY_CAT;
    } else if (state.pStats.hunger < 25) {
        colorPair = 4; // Yellow - hungry
        art = HUNGRY_CAT;
    } else if (state.pStats.energy < 20) {
        colorPair = 5; // Cyan for sleepy
        art = SLEEPY_CAT;
    }



    attron(COLOR_PAIR(colorPair));

    int line{};
    const char* p = art;
    std::string current;

    // Go through each character in the art
    while (*p) {
        if (*p == '\n') {
            // finds newline / print the current line
            mvprintw(y + line, x, "%s", current.c_str());
            current.clear();
            line++;
        } else {
            // Add character to current line
            current.push_back(*p);
        }
        ++p;
    }

    // Prints the last line if there is one
    if (!current.empty()) {
        mvprintw(y + line, x, "%s", current.c_str());
    }



    // Turns off color
    attroff(COLOR_PAIR(colorPair));
}

void Renderer::drawStats(const PetState& state, int y, int x) {

    mvprintw(y, x, "Stats");
    // Draws a bar for each stat
    drawBar(y + 2, x, "Hunger",      state.pStats.hunger,      20);
    drawBar(y + 3, x, "Happiness",   state.pStats.happiness,   20);
    drawBar(y + 4, x, "Energy",      state.pStats.energy,      20);
    drawBar(y + 5, x, "Cleanliness", state.pStats.cleanliness, 20);

    mvprintw(y + 6, x, "Status: %s", getPetStatusMsg(state));

    // Shows if the pet is alive
    mvprintw(y + 7, x, "Alive: %s", state.isAlive ? "For Now :|" : "no ;o");


}

void Renderer::drawCommands(int y, int x) {
    mvprintw(y, x, "Commands");
    mvprintw(y + 1, x, "[F]eed  [P]lay  [S]leep  [C]lean  [Q]uit");


}

void Renderer::drawEventLog(int y, int x, int maxLines) {
    mvprintw(y, x, "Log");

    // decide which messages to show
    int start = std::max(0, (int)m_events.size() - maxLines);
    int line{1};

    // Print each message
    for (int i = start; i < (int)m_events.size(); i++) {
        mvprintw(y + line, x, "%s", m_events[i].c_str());
        line++;
    }
}

// Draw a horizontal progress bar
void Renderer::drawBar(int y, int x, const std::string& label, int value, int width) {
    value = std::clamp(value, 0, 100);

    // Calculate how many characters should be filled
    int filled = (value * width) / 100;

    // Draw the label and opening bracket
    mvprintw(y, x, "%-11s [", label.c_str());

    // Draws the bar
    for (int i = 0; i < width; i++) {
        addch(i < filled ? '#' : ' ');  // '#' for filled, ' ' for empty
    }

    // Draw closing bracket and percentage
    addch(']');
    printw(" %3d", value);
}

// Draw a label with its value
void Renderer::drawLabelValue(int y, int x, const std::string& label,
                              const std::string& value, int width) {
    (void)width;  // Not used yet, but here for future formatting and void to remove error
    mvprintw(y, x, "%s: %s", label.c_str(), value.c_str());
}

void Renderer::clearEvents() {
    m_events.clear();
}



// TODO: Add drawSystemInfo implementation to show CPU, memory, etc.
// TODO: Add color to bars (red for low, green for high)
// TODO: Add different pet sprites based on mood
// TODO: Add blinking or animation to the pet
