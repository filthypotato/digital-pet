# Digital Pet - System Monitor Tamagotchi

A virtual pet game that runs in your terminal, where your pet's health is affected by your computer's system performance!

## Overview

This is a Tamagotchi-style virtual pet that lives in your terminal. The pet has four main stats:
- **Hunger** - Feed your pet to keep it satisfied
- **Happiness** - Play with your pet to keep it happy
- **Energy** - Let your pet sleep to restore energy
- **Cleanliness** - Clean your pet to keep it healthy

Your pet's stats are also affected by your computer's system metrics:
- High CPU usage makes the pet tired
- Low disk space makes the pet dirty
- High memory usage makes the pet hungry


## Building the Project

### Prerequisites

You need the ncurses library installed:

**Arch Linux:**
```bash
sudo pacman -S ncurses
# Or use the Makefile:
make install-deps-arch
```

**Ubuntu/Debian:**
```bash
sudo apt-get install libncurses5-dev
# Or use the Makefile:
make install-deps-debian
```

**Auto-detect (recommended):**
```bash
make install-deps
```

**macOS:**
```bash
brew install ncurses
```

### Compile

```bash
make
```

Or manually:
```bash
g++ -std=c++17 -Wall -Wextra *.cpp -o digital-pet -lncurses
```

### Run

```bash
make run
# or
./digital-pet
```

## Controls

- **F** - Feed your pet
- **P** - Play with your pet
- **S** - Put your pet to sleep
- **C** - Clean your pet
- **L** - Load saved game
- **Q** - Save and quit

## Key Improvements Made

### 1. Proper Game Class
The game logic is now encapsulated in a `Game` class instead of being in `main()`. This makes the code more organized and easier to maintain.

**Before:**
```cpp
// Everything in main()
int main() {
    NcursesApp app;
    Renderer renderer;
    PetState state;
    // Game loop...
}
```

**After:**
```cpp
// Clean separation
class Game {
    void init();
    void run();
    void update();
    void handleInput();
    void render();
};

int main() {
    Game game;
    game.init();
    game.run();
}
```

### 2. Better Frame Timing
Added proper frame timing to ensure consistent FPS regardless of system load.

### 3. Cleaner Main Function
`main.cpp` is now much simpler and focuses only on program initialization and error handling.

### 4. Build System
Added a Makefile for easy compilation and project management.

## TODO: Next Steps

### Priority 1 - Core Gameplay
- [ ] Implement `updatePetFromSystem()` to link system stats to pet needs
- [ ] Implement `decayStats()` for time-based stat degradation
- [ ] Implement `updateStatusFlags()` for boolean status flags
- [ ] Add pet death mechanics

### Priority 2 - Save/Load
- [ ] Track time elapsed since last save
- [ ] Apply decay based on time away
- [ ] Warn if pet died while user was gone

### Priority 3 - Visuals
- [ ] Different pet sprites for different moods
- [ ] Color-coded stat bars (green/yellow/red)
- [ ] Animations or blinking effects
- [ ] Better layout and spacing

### Priority 4 - System Info
- [ ] Dedicated panel for system metrics
- [ ] Visual health indicators
- [ ] Readable uptime format

### Priority 5 - Polish
- [ ] Pet naming
- [ ] Age counter
- [ ] Achievements system
- [ ] Handle terminal resizing
- [ ] More commands

## Architecture Notes

### Game Loop Flow
```
main()
  -> Game::init()
    -> Initialize ncurses
    -> Initialize renderer
    -> Load save file
  -> Game::run()
    -> while(running):
      -> update() - Update game state
      -> handleInput() - Process keyboard
      -> render() - Draw everything
      -> Frame timing
  -> Game::shutdown()
```

### Data Flow
```
/proc filesystem
    ↓
readHardwareStats()
    ↓
PetState (system metrics)
    ↓
updatePetFromSystem() [TODO]
    ↓
PetState (pet stats)
    ↓
Renderer::draw()
    ↓
Terminal display
```

## Debugging

The renderer currently shows debug information:
- CPU usage and raw CPU times
- Memory stats (total/available)
- Disk space usage
- System uptime

This debug info will be cleaned up once the system-to-pet mechanics are implemented.

## Known Issues

1. Terminal resizing not handled gracefully
2. No time-based stat decay yet
3. System metrics don't affect pet yet
4. Pet can't die yet
5. Save/load doesn't track time away


## License

This is a learning project. Feel free to use and modify as you wish!
