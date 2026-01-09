/* ncurses_app.hpp
   Reusable ncurses application wrapper
   Keeps init/cleanup/input handling in one place
*/

#ifndef NCURSES_APP_HPP
#define NCURSES_APP_HPP

#include <ncurses.h>
#include <string>

class NcursesApp {
public:
    NcursesApp();
    ~NcursesApp();

    // lifecycle
    void init();
    void shutdown();

    // main loop helpers
    void beginFrame();
    void endFrame();

    // input
    int pollInput();

    // drawing helpers
    void drawBorder();
    void drawCenteredText(int y, const std::string& text);


    // TODO: Add more drawing helpers as needed
    // Example: void drawBox(int y, int x, int height, int width);
    // Example: void drawSprite(int y, int x, const std::vector<std::string>& sprite);
    // Example: void drawHealthBar(int y, int x, int current, int max);
    // Example: void drawTextBox(int y, int x, const std::string& text);

    // TODO: Add color support methods
    // Example: void initColors();
    // Example: void setColor(int colorPair);
    // Example: void drawColoredChar(int y, int x, char ch, int color);

    // TODO: Add window/screen helpers
    // Example: int getScreenWidth() const;
    // Example: int getScreenHeight() const;
    // Example: bool isValidPosition(int y, int x) const;

    // TODO: Add timing/animation helpers
    // Example: void setFrameRate(int fps);
    // Example: double getDeltaTime() const;
    // Example: void sleep(int milliseconds);

    // state
    bool running() const;
    void stop();

private:
    bool m_running;

    // TODO: Add timing members if needed
    // Example: std::chrono::time_point<std::chrono::steady_clock> m_lastFrame;
    // Example: double m_deltaTime;
};

#endif // NCURSES_APP_HPP
