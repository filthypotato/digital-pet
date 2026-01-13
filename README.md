# System Monitor Pet 🐱💻

A Tamagotchi-style virtual pet that runs in your terminal. The pet's needs react to your computer's health (CPU, memory, disk) and you can interact using simple keyboard commands. This repository contains a ncurses-based demo with rendering, input handling, and initial system probes.

## Quick status

- Language: C++ (ncurses)
- Status: Work-in-progress — terminal UI, input handling and basic rendering are implemented; system metric calculations and gameplay rules still need work.

## Features

- Cute ASCII pet rendered in the terminal using ncurses
- Pet stats: Hunger, Happiness, Energy, Cleanliness
- Keyboard controls for interacting with the pet
- Reads system information from /proc (partial implementation)
- Event log system and simple UI

## Repository layout

- main.cpp - Main game loop and entry point
- ncurses_app.hpp / ncurses_app.cpp - ncurses wrapper and UI utilities
- proc.hpp / proc.cpp - Read system information from /proc filesystem (implement metric calculations here)
- Pet.hpp / Pet.cpp - Pet state and behavior logic
- Renderer.hpp / Renderer.cpp - Drawing and rendering logic

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

A simple g++ command (adjust filenames if you add/remove source files):

```bash
g++ -std=c++17 main.cpp ncurses_app.cpp proc.cpp Pet.cpp Renderer.cpp -lncurses -o pet
```

If your project already uses a build system (CMake/Make), prefer that. Here's a tiny Makefile snippet you can drop in as a starting point:

```makefile
CXX = g++
CXXFLAGS = -std=c++17 -O2
LDLIBS = -lncurses
SRCS = main.cpp ncurses_app.cpp proc.cpp Pet.cpp Renderer.cpp
OBJS = $(SRCS:.cpp=.o)

pet: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS) $(LDLIBS)

clean:
	rm -f pet $(OBJS)
```

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

## Current implementation notes

What works:

- Terminal UI with ncurses
- Basic rendering (pet sprite, stat bars, commands)
- Reading CPU times from /proc/stat
- User input handling
- Event log system

Planned / TODOs:

- Drive pet stat changes from system metrics in Pet.cpp
- Time-based stat decay and pet actions that modify stats
- Save / load functionality
- Pet death condition and different moods/sprites
- Colors and improved visuals

## Contributing

Contributions welcome! Good first tasks:

- Implement system metric calculations in proc.cpp
- Hook metrics into Pet.cpp to modify pet stats
- Add persistence (save/load)
- Improve UI and add colors

## License

If you have a preferred license, add it to a LICENSE file. If you want, I can add an MIT license template for you.

## Contact

Maintainer: filthypotato

---

Notes: I updated the README to add build instructions, a small Makefile, clearer TODOs, and contribution guidance while keeping the project marked as WIP.
