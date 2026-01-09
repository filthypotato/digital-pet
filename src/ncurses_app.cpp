/* ncurses_app.cpp
   Implementation of reusable ncurses wrapper
*/

#include "ncurses_app.hpp"

NcursesApp::NcursesApp()
    : m_running(true) {}

NcursesApp::~NcursesApp() {
    shutdown();
}

void NcursesApp::init() {
    initscr();              // start ncurses mode
    cbreak();               // disable line buffering
    noecho();               // don't echo input
    keypad(stdscr, TRUE);   // enable arrow keys
    curs_set(0);            // hide cursor
    timeout(100);           // non-blocking getch (100ms)

    if (has_colors()) {
        start_color();
        use_default_colors();

        // TODO: Initialize color pairs for your game
        // Example: init_pair(1, COLOR_RED, COLOR_BLACK);     // Enemy color
        // Example: init_pair(2, COLOR_GREEN, COLOR_BLACK);   // Player color
        // Example: init_pair(3, COLOR_YELLOW, COLOR_BLACK);  // Collectible color
        // Example: init_pair(4, COLOR_BLUE, COLOR_BLACK);    // UI color
    }
}

void NcursesApp::shutdown() {
    if (isendwin() == FALSE) {
        endwin();
    }
}

void NcursesApp::beginFrame() {
    erase();
}

void NcursesApp::endFrame() {
    refresh();
}

int NcursesApp::pollInput() {
    return getch();
}

void NcursesApp::drawBorder() {
    box(stdscr, 0, 0);
}

void NcursesApp::drawCenteredText(int y, const std::string& text) {
    int rows, cols;
    getmaxyx(stdscr, rows, cols);
    (void)rows;
    int x = (cols - static_cast<int>(text.size())) / 2;
    mvprintw(y, x, "%s", text.c_str());
}

bool NcursesApp::running() const {
    return m_running;
}

void NcursesApp::stop() {
    m_running = false;
}

// TODO: Implement additional drawing methods
// Example implementation of drawBox:
// void NcursesApp::drawBox(int y, int x, int height, int width) {
//     for (int i = 0; i < height; i++) {
//         mvaddch(y + i, x, '|');
//         mvaddch(y + i, x + width - 1, '|');
//     }
//     for (int i = 0; i < width; i++) {
//         mvaddch(y, x + i, '-');
//         mvaddch(y + height - 1, x + i, '-');
//     }
// }

// TODO: Implement color methods
// Example:
// void NcursesApp::setColor(int colorPair) {
//     attron(COLOR_PAIR(colorPair));
// }

// TODO: Implement screen dimension getters
// Example:
// int NcursesApp::getScreenWidth() const {
//     return COLS;
// }
// int NcursesApp::getScreenHeight() const {
//     return LINES;
// }

// TODO: Implement validation helpers
// Example:
// bool NcursesApp::isValidPosition(int y, int x) const {
//     return (y > 0 && y < LINES - 1 && x > 0 && x < COLS - 1);
// }
