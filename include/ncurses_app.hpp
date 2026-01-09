/* ncurses_app.hpp
   Wrapper class for ncurses library
   Handles initialization, cleanup, and basic drawing
*/

#ifndef NCURSES_APP_HPP
#define NCURSES_APP_HPP

#include <ncurses.h>
#include <string>

class NcursesApp {
public:
    NcursesApp();
    ~NcursesApp();

    void init();
    void shutdown();

    void beginFrame();
    void endFrame();

    int pollInput();

    void drawBorder();
    void drawCenteredText(int y, const std::string& text);

    // TODO PHASE 3: Add more drawing helpers when you need them
    // Ideas: drawBox, drawBar, drawSprite

    bool running() const;
    void stop();

private:
    bool m_running;
};

#endif
