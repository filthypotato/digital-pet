/* ncurses_app.cpp
   Basic wrapper around ncurses library
*/

#include "ncurses_app.hpp"
#include "Renderer.hpp"
#include <ncurses.h>

// Constructor - start with app running
NcursesApp::NcursesApp()
    : m_running(true) {}

// Destructor - make sure ncurses shuts down cleanly
NcursesApp::~NcursesApp() {
    shutdown();
}

// Initialize ncurses with all the settings we need
void NcursesApp::init() {
    initscr();              // Start ncurses mode
    cbreak();               // Disable line buffering (get keys immediately)
    noecho();               // Don't print what user types
    keypad(stdscr, TRUE);   // Enable arrow keys and function keys
    curs_set(0);            // Hide the cursor
    nodelay(stdscr, TRUE);  // Make getch() truly non-blocking
    timeout(0);             // Don't wait at all for input

    // Enables double buffering to prevent flicker
    intrflush(stdscr, FALSE);
    scrollok(stdscr, FALSE);

    // Set up colors if the terminal supports them
    if (has_colors()) {
        start_color();
        use_default_colors();

        // In your init, after start_color():
        init_pair(1, COLOR_GREEN, COLOR_BLACK);  // Happy = green
        init_pair(2, COLOR_RED, COLOR_BLACK);    // Angry = red
        init_pair(3, COLOR_BLUE, COLOR_BLACK);   // Sad = blue
        init_pair(4, COLOR_YELLOW, COLOR_BLACK); // Yellow = hungry
        init_pair(5, COLOR_CYAN, COLOR_BLACK);   // Cyan = Sleepy
        // When drawing:
        attron(COLOR_PAIR(1));  // Turn on green
        attroff(COLOR_PAIR(1)); // Turn off green
        // TODO: Define color pairs when you want colors
        // Example: init_pair(1, COLOR_RED, COLOR_BLACK);
        //          init_pair(2, COLOR_GREEN, COLOR_BLACK);
    }
}

// Cleans up ncurses before exiting
void NcursesApp::shutdown() {
    // Only call endwin() if ncurses is still active
    if (isendwin() == FALSE) {
        endwin();
    }
}

// Start a new frame - DON'T clear to prevent border flicker
void NcursesApp::beginFrame() {
    // Empty - we draw over old content to prevent flicker
}

// End the frame by showing everything drawn
void NcursesApp::endFrame() {
    refresh();  // Display what is drawn
}

// Check if user pressed a key (non-blocking)
int NcursesApp::pollInput() {
    return getch();  // Returns ERR if no key pressed
}

// Draw a border around the entire screen
void NcursesApp::drawBorder() {
    box(stdscr, 0, 0);  // Draw box on standard screen
}

// Draw text centered horizontally at the given y position
void NcursesApp::drawCenteredText(int y, const std::string& text) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);  // Get screen size
    (void)rows;  // Dont need rows. void to silice error

    // Calculate x position to center the text
    int x = (cols - static_cast<int>(text.size())) / 2;

    // Draw the text
    mvprintw(y, x, "%s", text.c_str());
}

// Check if the app should keep running
bool NcursesApp::running() const {
    return m_running;
}

// Tell the app to stop running which exits the main loop
void NcursesApp::stop() {
    m_running = false;
}

// TODO: Add a function to draw a progress bar
// TODO: Add a function to draw a box at specific coordinates
// TODO: Add a function to check if coordinates are within screen bounds
