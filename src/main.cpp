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

Core Gameplay:
- Implement updatePetFromSystem() to link system health to pet needs
  - High CPU usage -> pet loses energy
  - Low disk space -> pet loses cleanliness
  - High memory usage -> pet loses hunger

- Implement decayStats() for time-based stat reduction
  - All stats slowly decrease over time
  - Decay rate should be balanced for gameplay

- Implement updateStatusFlags() to set boolean flags
  - isHungry = (hunger < 30)
  - isHappy = (happiness > 50)
  - hasEnergy = (energy > 30)
  - isClean = (cleanliness > 30)

- Add pet death condition
  - Pet dies when multiple stats are critically low
  - Or after extended period without care

Save/Load System:
/ Already have save and load
- Calculate time elapsed since last save
- Apply stat decay based on time away
- Add warning if pet died while user was away

Enhanced Visuals:
- Add different pet sprites for different moods
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
