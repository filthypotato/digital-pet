/* main.cpp
   System Monitor Pet - Tamagotchi style
   A virtual pet whose needs are affected by your computer's health
*/

#include "Game.hpp"
#include <iostream>

int main() {
    try {
        // Create and initialize the game
        Game game;
        game.init();

        // main game loop
        game.run();

        // shuts down game and cleans up memory
        game.shutdown();

        // Clear screen to avoid UI sticking like before
        std::cout << "\033[2J\033[H" << std::flush;

    } catch (const std::exception& e) { // handles error exeception
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

/* TODO List for Future Development:



// Unsure if i want to add decaying stats over time or just based on system metrics
- Implement decayStats() for time-based stat reduction
  - All stats slowly decrease over time
  - Decay rate should be balanced for gameplay

- Add pet death condition
  - Add create new pet when pet dies
  - Or after extended period without care

Save/Load System:
/ Already have save and load
- Calculate time elapsed since last save
- Apply stat decay based on time away
- Add warning if pet died while user was away

Enhanced Visuals:
- Add color coding to stat bars (green/yellow/red)
- Add animations or blinking effects
- Improve layout and spacing

System Info Display:
- Show CPU/memory/disk in dedicated panel
- Add visual indicators for system health
- Display system uptime in readable format

Polish:
- Add pet name customization
- Add age counter based on uptime
- Add achievements/milestones
- Handle terminal resizing gracefully
- Add more interactive commands
*/
