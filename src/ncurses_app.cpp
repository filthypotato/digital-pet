/* ncurses_app.cpp
   Basic wrapper around ncurses library
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

        // TODO PHASE 6: Set up color pairs if you want colors
        // init_pair(1, COLOR_RED, COLOR_BLACK);
        // init_pair(2, COLOR_GREEN, COLOR_BLACK);
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

// TODO PHASE 3 or later: Add helper functions you need
// Maybe a function to draw a bar graph?
// Maybe a function to draw a box?
// Maybe a function to validate coordinates?
