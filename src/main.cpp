/* main.cpp
   System Monitor Pet - Tamagotchi style
*/

#include "ncurses_app.hpp"
#include "proc.hpp"

// PHASE 0 — FOUNDATION
// TODO: Create a struct for pet stats (hunger, happiness, energy, cleanliness)
// TODO: Create a struct for system metrics (cpu, memory, disk, uptime)
// TODO: Create a struct for pet state that holds everything




// TODO: Write function to read memory usage from /proc/meminfo
// TODO: Write function to read disk space (use statvfs or df command)
// TODO: Write function to read uptime from /proc/uptime

// TODO: Write function that translates system stats into pet needs
//       Example: high CPU = hunger increases, low disk = cleanliness drops


// PHASE 2 — STATE & PERSISTENCE
// TODO: Write function to save pet state to a file
// TODO: Write function to load pet state from a file
// TODO: Calculate time elapsed since last run
// TODO: Apply decay to stats based on time away


// PHASE 3 — UI & INTERACTION
// TODO: Draw the pet (simple ASCII art)
// TODO: Draw stat bars :for each need
// TODO: Draw system metrics
// TODO: Handle user commands (feed, play, sleep, clean)


int main() {
    CpuTimes out;

    NcursesApp app{};
    app.init();

    // TODO: Create your pet state variable here

    // TODO: Try to load saved state, if it doesn't exist, create new pet

    while (app.running()) {
        app.beginFrame();
        app.drawBorder();

       readProcStats(out);


        // TODO PHASE 3: Draw UI here
        // - pet visual
        // - stat bars
        // - system info
        // - event log
        // - commands
        move(2, 0);
        clrtoeol();
        mvprintw(10, 25, "Press Q to quit.");

        // Handle input
        int ch = app.pollInput();
        if (ch == 'q' || ch == 'Q') {
            // TODO PHASE 2: Save before quitting
            app.stop();
        }
        // TODO: Handle other commands ([f]eed, [p]et, [s]leep, [c]are)

        app.endFrame();
    }

    return 0;
}
