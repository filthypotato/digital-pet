# System Monitor Pet 🐱💻

A Tamagotchi-style virtual pet that lives in your terminal! Your pet's needs are affected by your computer's health.

## What This Does

- Shows a cute ASCII pet in your terminal
- Pet has needs: hunger, happiness, energy, cleanliness
- You can interact with your pet using keyboard commands
- Pet's needs change based on your computer's CPU, memory, and disk usage

## Files Overview

- **main.cpp** - Main game loop and program entry point
- **ncurses_app.hpp/cpp** - Wrapper for ncurses library (handles terminal UI)
- **proc.hpp/cpp** - Reads system information from /proc filesystem
- **Pet.hpp/cpp** - Pet state and behavior logic
- **Renderer.hpp/cpp** - Draws everything on screen
- **Makefile** - Build instructions

## How to Build

You need ncurses library installed:
```bash
# On Ubuntu/Debian:
sudo apt-get install libncurses5-dev libncursesw5-dev

# On Fedora:
sudo dnf install ncurses-devel

# On macOS:
brew install ncurses
```

Then compile:
```bash
make
```

## How to Run

```bash
./pet
```

## Controls

- **F** - Feed your pet
- **P** - Play with your pet
- **S** - Put pet to sleep
- **C** - Clean your pet
- **Q** - Quit

## Current Status

This is a work-in-progress! Many features are marked with `// TODO:` comments.

### What Works Now:
✅ Terminal UI with ncurses
✅ Basic rendering (pet sprite, stat bars, commands)
✅ Reading CPU times from /proc/stat
✅ User input handling
✅ Event log system

### What's Not Implemented Yet:
❌ Calculating actual CPU/memory/disk percentages
❌ Pet stat changes based on system metrics
❌ Time-based stat decay
❌ Save/load system
❌ Pet actions actually changing stats
❌ Pet death condition
❌ Colors
❌ Different pet moods/sprites

## Learning Path

Follow the TODO comments in the code! They're organized into phases:

1. **Phase 1** - Get system monitoring working (CPU, memory, disk)
2. **Phase 2** - Add save/load functionality
3. **Phase 3** - Implement pet actions (feed, play, etc)
4. **Phase 4** - Connect system health to pet needs
5. **Phase 5** - Add better visuals and colors
6. **Phase 6** - Polish and extra features

## Tips

- Read through the comments in each file to understand what each function does
- Start with the TODOs in `proc.cpp` to get system monitoring working
- Then move to `Pet.cpp` to implement pet behavior
- Test frequently! Run `make && ./pet` after each change
- If something doesn't compile, read the error message carefully

## Example TODO to Start With

In `proc.cpp`, try implementing this function:
```cpp
int calculateCpuPercentage(const CpuTimes& prev, const CpuTimes& curr) {
    // Calculate difference in total time
    unsigned long prevTotal = prev.user + prev.nice + prev.system + 
                              prev.idle + prev.iowait + prev.irq + 
                              prev.softirq + prev.steal;
    unsigned long currTotal = curr.user + curr.nice + curr.system + 
                              curr.idle + curr.iowait + curr.irq + 
                              curr.softirq + curr.steal;
    unsigned long totalDiff = currTotal - prevTotal;
    
    // Calculate difference in idle time
    unsigned long idleDiff = curr.idle - prev.idle;
    
    // Calculate CPU usage percentage
    if (totalDiff == 0) return 0;
    return 100 * (totalDiff - idleDiff) / totalDiff;
}
```

Happy coding! 🚀
