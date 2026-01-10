/* ncurses_app.hpp
   Wrapper class for ncurses library
   Handles initialization, cleanup, and basic drawing
*/
#pragma once

#include <ncurses.h>
#include <string>

class NcursesApp {
public:
    // Constructor - sets up initial state
    NcursesApp();

    // Destructor - ensures cleanup happens
    ~NcursesApp();

    // Initialize ncurses mode (call once at start)
    void init();

    // Clean up ncurses (call once at end)
    void shutdown();

    // Call at the start of each frame - clears screen
    void beginFrame();

    // Call at the end of each frame - displays everything
    void endFrame();

    // Check for keyboard input (returns character or ERR if none)
    int pollInput();

    // Draw a box around the screen edges
    void drawBorder();

    // Draw text centered horizontally at row y
    void drawCenteredText(int y, const std::string& text);

    // TODO: Add drawBox() to draw boxes at specific positions
    // TODO: Add drawBar() to draw progress bars
    // TODO: Add drawSprite() to draw multi-line ASCII art

    // Check if the app should keep running
    bool running() const;

    // Stop the main loop
    void stop();

private:
    bool m_running;  // Controls the main game loop
};

