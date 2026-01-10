// Renderer.hpp
// Handles all drawing and visual presentation
#pragma once
#include <string>
#include <vector>

// Forward declarations (full definitions in Pet.hpp)
struct PetState;
struct SystemMetrics;

// The Renderer class manages all visual output
class Renderer {
public:
    Renderer() = default;

    // Initialize renderer (call once after ncurses init)
    void init();

    // Draw everything for one frame
    void draw(const PetState& state);

    // Cleanup renderer (call before ncurses shutdown)
    void shutdown();

    // Add a message to the event log
    void pushEvent(std::string msg);

private:
    // Draw the window frame and title
    void drawFrame();
    
    // Draw the pet ASCII art at position (y, x)
    void drawPetVisual(int y, int x);
    
    // Draw the pet's stat bars
    void drawStats(const PetState& state, int y, int x);
    
    // Draw system information (CPU, memory, etc)
    void drawSystemInfo(const PetState& state, int y, int x);
    
    // Draw the available commands
    void drawCommands(int y, int x);
    
    // Draw recent events/messages
    void drawEventLog(int y, int x, int maxLines);

    // Helper: draw a progress bar with label and value
    void drawBar(int y, int x, const std::string& label, int value, int width);
    
    // Helper: draw a label and value pair
    void drawLabelValue(int y, int x, const std::string& label, 
                       const std::string& value, int width);

    // Storage for event messages
    std::vector<std::string> m_events{};

    // Screen dimensions (updated each frame)
    int m_width{};
    int m_height{};
};

// TODO: Add color support to make different stats different colors
// TODO: Add animations (make the pet move or blink)
// TODO: Add different pet sprites based on mood
// TODO: Draw system info section showing CPU/memory/disk
