/* main.cpp
   System Monitor Pet - Tamagotchi style
   A virtual pet whose needs are affected by your computer's health
*/

#include "Input.hpp"
#include "ncurses_app.hpp"
#include "proc.hpp"
#include "Renderer.hpp"
#include "Pet.hpp"
#include "Load_Save.hpp"
#include <chrono>
#include <thread>
#include <iostream>
// MAIN GAME LOOP

int main() {
    // ncurses for terminal UI
    NcursesApp app{};
    app.init();

    // Renderer for drawing
    Renderer renderer{};
    renderer.init();

    // Pet starts with default stats (all at 50%)
    PetState state = loadGame();

    if (!state.isAlive) {
      state.isAlive = true;  // Pet starts alive!
    }


    // Welcome message log
    renderer.pushEvent("Welcome! Your pet needs you!");

    // MAIN GAME LOOP - runs until user quits
    while (app.running()) {
        // Start of frame - clears the screen
        app.beginFrame();

        // Read current system stats from /proc/stat
        if (readCpuStats(state.cpuOut)) {
            // reads CPU times
            if (state.hasPrevCpu) {
              state.sMetrics.cpuPet = calcCpuPercent(state.prevCpu, state.cpuOut);
            }
            state.prevCpu = state.cpuOut;
            state.hasPrevCpu = true;
        }

        if (readMemStats(state.memOut)) {
         // Successfully read memory stats and calculates percentage
         state.sMetrics.memPet = calcMemPercent(state.memOut);
        }

        // TODO: Add file paths for ones you want to track specifically
        const std::vector<const char*> diskPaths = {
          "/mnt",
          "/mnt/drive1",
          "/home"
        };

        if (readDiskInfo(diskPaths, state.diskOut)) {
          state.sMetrics.diskPet = state.diskOut.percentUsed;
        }

        // find keys in Input.cpp
        keyboardInput(app, renderer, state);

        // UPDATE PET STATE
        // TODO: Call function to update pet stats based on system metrics
        // TODO: Call function to apply time-based decay
        // TODO: Call function to update status flags (isHungry, isHappy, etc)

        // RENDER EVERYTHING
        renderer.draw(state);  // Draw the pet and all UI elements

        app.endFrame();  // Show everything on screen

        // Frame rate limiting - 10 FPS (reduces flicker)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    // exits ncurses
    app.shutdown();

    // fully clears screen to avoid UI sticking when quiting
    std::cout << "\033[2J\033[H" << std::flush;

    return 0;
}


// First - Basic System Monitoring:
// TODO: Implement readUptime() in proc.cpp

// Second - Save/Load System:
// TODO: Calculate time elapsed since last save
// TODO: Apply stat decay based on time away

// Third - Pet Behavior:
// TODO: Implement updatePetFromSystem() to link system health to pet needs
// TODO: Implement decayStats() for time-based stat reduction
// TODO: Implement updateStatusFlags() to set isHungry, isHappy, etc
// TODO: Add pet death condition when stats get too low

// Fourth - Enhanced Visuals:
// TODO: Add drawSystemInfo() to Renderer to show CPU/memory/disk in a nice panel
// TODO: Add different pet sprites for different moods (happy, sad, tired)
// TODO: Add color to stat bars (green = good, yellow = warning, red = critical)
// TODO: Add animations or blinking to the pet

// Fifth - Polish:
// TODO: Add sound effects (terminal beep?) for important events
// TODO: Add achievements or milestones
// TODO: Add pet name that user can choose
// TODO: Add pet age counter (based on uptime)
// TODO: Make terminal resizing work properly
