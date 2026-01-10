# System Monitor Pet 🐱💻

A Tamagotchi-style virtual pet that lives in your terminal. Your pet's needs respond to your computer's health (CPU, memory, disk), and you can interact using simple keyboard commands.

## Features

- Cute ASCII pet rendered in terminal using ncurses
- Pet stats: Hunger, Happiness, Energy, Cleanliness
- Keyboard controls for interacting with your pet
- Reads system information from /proc to influence pet behavior (work in progress)
- Event log system and basic UI

## Repository contents

- main.cpp - Main game loop and entry point
- ncurses_app.hpp / ncurses_app.cpp - ncurses wrapper (terminal UI)
- proc.hpp / proc.cpp - Read system information from /proc filesystem
- Pet.hpp / Pet.cpp - Pet state and behavior logic
- Renderer.hpp / Renderer.cpp - Drawing and rendering logic
- Makefile - Build instructions

## Prerequisites

You need the ncurses development libraries installed.

On Ubuntu/Debian:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

On Fedora:
```bash
sudo dnf install ncurses-devel
```

On Arch Linux:
```bash
sudo pacman -S ncurses
```

On macOS (Homebrew):
```bash
brew install ncurses
```

## Build

This builds the `pet` executable.

## Run

Start the pet in your terminal:

```bash
./pet
```

If your terminal becomes unresponsive after an abnormal exit, run `reset` to restore state.

## Controls

- F — Feed your pet
- P — Play with your pet
- S — Put the pet to sleep
- C — Clean your pet
- Q — Quit the application

Controls are case-insensitive.

## Current Status

This project is a work-in-progress. The UI, input handling, and basic rendering are implemented, but system metrics and gameplay logic are still being developed.

What works:

- Terminal UI with ncurses
- Basic rendering (pet sprite, stat bars, commands)
- Reading CPU times from /proc/stat
- User input handling
- Event log system

Planned / TODOs:

- Calculate CPU / memory / disk usage percentages
- Drive pet stat changes from system metrics
- Time-based stat decay and pet actions that modify stats
- Save / load functionality
- Pet death condition and different moods/sprites
- Colors and improved visuals

## Development notes

Follow the // TODO comments in the code. A good starting point:

1. Implement system metric calculations in proc.cpp (CPU, memory, disk)
2. Hook metrics into Pet.cpp to modify pet stats
3. Add persistence (save/load)
4. Polish UI and add colors

Example function to implement in proc.cpp:

```cpp
int calculateCpuPercentage(const CpuTimes& prev, const CpuTimes& curr) {
    unsigned long prevTotal = prev.user + prev.nice + prev.system + 
                              prev.idle + prev.iowait + prev.irq + 
                              prev.softirq + prev.steal;
    unsigned long currTotal = curr.user + curr.nice + curr.system + 
                              curr.idle + curr.iowait + curr.irq + 
                              curr.softirq + curr.steal;
    unsigned long totalDiff = currTotal - prevTotal;
    unsigned long idleDiff = curr.idle - prev.idle;
    if (totalDiff == 0) return 0;
    return 100 * (totalDiff - idleDiff) / totalDiff;
}
```

## License

This repository does not currently include a license. Add a LICENSE file if you want to set one.

