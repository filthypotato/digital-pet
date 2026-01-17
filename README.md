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

### Run

```bash
make run
# or
./digital-pet
```

```bash
Change variables in Pet.cpp. Change to how you want the stats to decay

const float cpuUsageToAffectEngery{5}; // change to which % you want stats to start decaying
const float diskUsageToAffectCleanliness{10}; // change % here
const float memUsageToAffectCleanliness{27};  // change % here
constexpr float ENERY_DECAY{3.0f};  // loses 1 tick of energy every 3 seconds
constexpr float HUNGER_DECAY{4.0f}; // loses 1 tick of hunger every 4 seconds
constexpr float CLEAN_DECAY{3.0f};  // loses 1 tick of cleanliness every 3 seconds
```

## Controls

- **F** - Feed your pet
- **P** - Play with your pet
- **S** - Put your pet to sleep
- **C** - Clean your pet
- **L** - Load saved game
- **Q** - Save and quit

## TODO: Next Steps


### Priority 1 - Save/Load
- [ ] Track time elapsed since last save
- [ ] Apply decay based on time away - maybe
- [ ] Warn if pet died while user was gone - part of above, mabe

### Priority 2 - Visuals
- [ ] Animations or blinking effects
- [ ] Better layout and spacing

### Priority 3 - System Info
- [ ] Dedicated panel for system metrics
- [ ] Visual health indicators

### Priority 4 - Polish
- [ ] Add pet levels
- [ ] Pet naming
- [ ] Age counter
- [ ] Achievements system
- [ ] Handle terminal resizing
- [ ] More commands

## Debugging

The renderer currently shows debug information:
Press 'd' to turn off/on debug menu
- CPU usage and raw CPU times
- Memory stats (total/available)
- Disk space usage
- System uptime


## Known Issues

1. Terminal resizing not handled gracefully
2. No time-based stat decay yet
3. System metrics don't affect pet yet


## License

This is a learning project. Feel free to use and modify as you wish!
