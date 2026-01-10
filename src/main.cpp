/* main.cpp
   System Monitor Pet - Tamagotchi style
   A virtual pet whose needs are affected by your computer's health
*/

#include "ncurses_app.hpp"
#include "proc.hpp"
#include "Renderer.hpp"
#include "Pet.hpp"
#include <chrono>
#include <thread>

// MAIN GAME LOOP

int main() {
    // Initialize ncurses for terminal UI
    NcursesApp app{};
    app.init();

    // Initialize the renderer for drawing
    Renderer renderer{};
    renderer.init();

    // Create the pet with default stats (all at 50%)
    PetState state{};
    state.isAlive = true;  // Pet starts alive!

    // Storage for CPU readings

    // Add a welcome message to the log
    renderer.pushEvent("Welcome! Your pet needs you!");

    // MAIN GAME LOOP - runs until user quits
    while (app.running()) {
        // Start of frame - clears the screen
        app.beginFrame();

        // Read current system stats from /proc/stat
        if (readProcStats(state.cpuOut)) {
            // Successfully read CPU times
            // TODO: Calculate actual CPU percentage and update pet.sMetrics.cpu
            // For now, we'll just store a placeholder value
            state.sMetrics.cpu = 0;  // calculate this later
        }

        // HANDLE USER INPUT
        int ch = app.pollInput();  // Get keyboard input (or ERR if none)

        if (ch == 'q' || ch == 'Q') {
            // User wants to quit
            // TODO PHASE 2: Save pet state before quitting
            app.stop();
        }
        else if (ch == 'f' || ch == 'F') {
            feedPet(state);
            renderer.pushEvent("You fed your pet!");
        }
        else if (ch == 'p' || ch == 'P') {
            playWithPet(state);
            renderer.pushEvent("You played with your pet!");
        }
        else if (ch == 's' || ch == 'S') {
            sleepPet(state);
            renderer.pushEvent("Your pet is sleeping...");
        }
        else if (ch == 'c' || ch == 'C') {
            cleanPet(state);
            renderer.pushEvent("You cleaned your pet!");
        }

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

    // Cleanup and exit
    return 0;
}

// TODO LIST FOR EXPANDING THE PROJECT

// PHASE 1 - Basic System Monitoring:
// TODO: Implement calculateCpuPercentage() in proc.cpp
// TODO: Implement readMemoryStats() in proc.cpp
// TODO: Implement readDiskStats() in proc.cpp
// TODO: Implement readUptime() in proc.cpp

// PHASE 2 - Save/Load System:
// TODO: Create saveToFile() function to save pet state as JSON or binary
// TODO: Create loadFromFile() function to load saved pet
// TODO: Calculate time elapsed since last save
// TODO: Apply stat decay based on time away

// PHASE 4 - Pet Behavior:
// TODO: Implement updatePetFromSystem() to link system health to pet needs
// TODO: Implement decayStats() for time-based stat reduction
// TODO: Implement updateStatusFlags() to set isHungry, isHappy, etc
// TODO: Add pet death condition when stats get too low

// PHASE 5 - Enhanced Visuals:
// TODO: Add drawSystemInfo() to Renderer to show CPU/memory/disk
// TODO: Add different pet sprites for different moods (happy, sad, tired)
// TODO: Add color to stat bars (green = good, yellow = warning, red = critical)
// TODO: Add animations or blinking to the pet

// PHASE 6 - Polish:
// TODO: Add sound effects (terminal beep?) for important events
// TODO: Add achievements or milestones
// TODO: Add pet name that user can choose
// TODO: Add pet age counter (based on uptime)
// TODO: Make terminal resizing work properly
