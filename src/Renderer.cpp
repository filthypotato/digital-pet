// Renderer.cpp
// Implementation of rendering functions
#include "Renderer.hpp"
#include "proc.hpp"
#include "Pet.hpp"
#include <ncurses.h>
#include <algorithm>

// ASCII art for the pet (a simple cat)
static const char* CAT_ART = R"(
 /\_/\
( o.o )
 > ^ <
)";

// Initialize the renderer - get screen size
void Renderer::init() {
    getmaxyx(stdscr, m_height, m_width);
}

// Cleanup (currently nothing to do but wanted to have just in case
void Renderer::shutdown() {
    // If you create sub-windows later, delete them here with delwin()
}

// Add an event message to the log
void Renderer::pushEvent(std::string msg) {
    m_events.push_back(std::move(msg));

    // Keep only the last 50 messages to avoid memory issues
    if (m_events.size() > 50) {
        m_events.erase(m_events.begin());
    }
}

// Main draw function - draws everything for one frame
void Renderer::draw(const PetState& state) {
    // Update screen size in case terminal was resized
    getmaxyx(stdscr, m_height, m_width);

    // Clear the screen
    erase();

    // Draw the window frame
    drawFrame();

    // Draw all the UI elements at their positions
    // You can adjust these coordinates to rearrange the layout
    drawPetVisual(2, 2);                      // Pet in top-left
    drawStats(state, 2, 25);                  // Stats next to pet
    drawCommands(m_height - 6, 2);            // Commands at bottom-left
    drawEventLog(m_height - 6, 35, 4);        // Log at bottom-right

    // TEMP: /proc debug
    mvprintw(15, 2, "PROC cpu:");
    mvprintw(16, 2, "user:   %llu", state.cpuOut.user);
    mvprintw(17, 2, "system: %llu", state.cpuOut.system);
    mvprintw(18, 2, "idle:   %llu", state.cpuOut.idle);
    mvprintw(19, 2, "steal:  %llu", state.cpuOut.steal);

    // Actually display everything (ncurses requires this)
    refresh();
}

// Draw the border and title
void Renderer::drawFrame() {
    box(stdscr, 0, 0);                        // Draw border around screen
    mvprintw(0, 2, " digital-pet ");          // Title in top border
}

// Draw the pet's ASCII art
void Renderer::drawPetVisual(int y, int x) {
    // Print the multi-line ASCII art line by line
    int line{};
    const char* p = CAT_ART;
    std::string current;

    // Go through each character in the art
    while (*p) {
        if (*p == '\n') {
            // Found a newline - print the current line
            mvprintw(y + line, x, "%s", current.c_str());
            current.clear();
            line++;
        } else {
            // Add character to current line
            current.push_back(*p);
        }
        ++p;
    }

    // Print the last line if there is one
    if (!current.empty()) {
        mvprintw(y + line, x, "%s", current.c_str());
    }
}

// Draw all the pet's stat bars
void Renderer::drawStats(const PetState& state, int y, int x) {
    mvprintw(y, x, "Stats");

    // Draw a bar for each stat (values are 0-100)
    drawBar(y + 2, x, "Hunger",      state.pStats.hunger,      20);
    drawBar(y + 3, x, "Happiness",   state.pStats.happiness,   20);
    drawBar(y + 4, x, "Energy",      state.pStats.energy,      20);
    drawBar(y + 5, x, "Cleanliness", state.pStats.cleanliness, 20);

    // Show if the pet is alive
    mvprintw(y + 7, x, "Alive: %s", state.isAlive ? "yes" : "no");


}

// Draw the available commands
void Renderer::drawCommands(int y, int x) {
    mvprintw(y, x, "Commands");
    mvprintw(y + 1, x, "[F]eed  [P]lay  [S]leep  [C]lean  [Q]uit");


}

// Draw the event log (recent messages)
void Renderer::drawEventLog(int y, int x, int maxLines) {
    mvprintw(y, x, "Log");

    // Calculate which messages to show (most recent ones)
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
    // Make sure value is in valid range
    value = std::clamp(value, 0, 100);

    // Calculate how many characters should be filled
    int filled = (value * width) / 100;

    // Draw the label and opening bracket
    mvprintw(y, x, "%-11s [", label.c_str());

    // Draw the bar itself
    for (int i = 0; i < width; i++) {
        addch(i < filled ? '#' : ' ');  // '#' for filled, ' ' for empty
    }

    // Draw closing bracket and percentage
    addch(']');
    printw(" %3d", value);
}

// Draw a label with its value (FIXED: added width parameter)
void Renderer::drawLabelValue(int y, int x, const std::string& label,
                              const std::string& value, int width) {
    (void)width;  // Not used yet, but here for future formatting
    mvprintw(y, x, "%s: %s", label.c_str(), value.c_str());
}

// TODO: Add drawSystemInfo implementation to show CPU, memory, etc.
// TODO: Add color to bars (red for low, green for high)
// TODO: Add different pet sprites based on mood
// TODO: Add blinking or animation to the pet
