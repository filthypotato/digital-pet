#pragma once

#include "ncurses_app.hpp"
#include "Renderer.hpp"
#include "Pet.hpp"

class Game {
public:
    Game();
    ~Game();

    void init();
    void run();
    void shutdown();

private:
    // Updates game logic during main loop
    void update(float dtSeconds);

    void handleInput();

    // Renders the current frame its at
    void render();

    // Game components
    NcursesApp app;
    Renderer renderer;
    PetState state;

    // Frame timing
    static constexpr int TARGET_FPS = 10;
    static constexpr int FRAME_DELAY_MS = 1000 / TARGET_FPS;
};
