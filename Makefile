# Makefile for Digital Pet Project (with src/ and include/ structure)

# Compiler and flags
CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -pedantic -O2 -Iinclude
LDFLAGS = -lncurses

# Directories
SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)/obj

# Source files (automatically find all .cpp files in src/)
SOURCES = $(wildcard $(SRC_DIR)/*.cpp)

# Object files (convert src/file.cpp to build/obj/file.o)
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# Output executable
TARGET = digital-pet

# Default target
all: $(TARGET)

# Create necessary directories
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Link object files to create executable
$(TARGET): $(OBJ_DIR) $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(LDFLAGS)
	@echo "Build complete! Run with: ./$(TARGET)"

# Compile source files to object files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean build artifacts
clean:
	rm -rf $(BUILD_DIR) $(TARGET) savegame.dat

# Clean and rebuild
rebuild: clean all

# Run the program
run: $(TARGET)
	./$(TARGET)

# Install ncurses if needed (Ubuntu/Debian)
install-deps-debian:
	sudo apt-get update
	sudo apt-get install -y libncurses5-dev libncursesw5-dev

# Install ncurses if needed (Arch Linux)
install-deps-arch:
	sudo pacman -S --needed ncurses

# Auto-detect and install (tries Arch first, then Debian)
install-deps:
	@if command -v pacman > /dev/null 2>&1; then \
		echo "Detected Arch Linux, installing with pacman..."; \
		$(MAKE) install-deps-arch; \
	elif command -v apt-get > /dev/null 2>&1; then \
		echo "Detected Debian/Ubuntu, installing with apt-get..."; \
		$(MAKE) install-deps-debian; \
	else \
		echo "Could not detect package manager. Please install ncurses manually."; \
		echo "Arch Linux: sudo pacman -S ncurses"; \
		echo "Ubuntu/Debian: sudo apt-get install libncurses5-dev"; \
	fi

# Show help
help:
	@echo "Available targets:"
	@echo "  all               - Build the project (default)"
	@echo "  clean             - Remove build artifacts"
	@echo "  rebuild           - Clean and rebuild"
	@echo "  run               - Build and run the program"
	@echo "  install-deps      - Auto-detect and install ncurses"
	@echo "  install-deps-arch - Install ncurses on Arch Linux"
	@echo "  install-deps-debian - Install ncurses on Ubuntu/Debian"
	@echo "  help              - Show this help message"
	@echo ""
	@echo "Project structure:"
	@echo "  src/         - Source files (.cpp)"
	@echo "  include/     - Header files (.hpp)"
	@echo "  build/obj/   - Object files (.o)"

.PHONY: all clean rebuild run install-deps install-deps-arch install-deps-debian help
