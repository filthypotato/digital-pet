#pragma once

#include "ncurses_app.hpp"
#include "Renderer.hpp"
#include "Pet.hpp"

class Game {
public:
    Game();
    ~Game();

    // Init game
    void init();

    // Runs the main game loop
    void run();

    // clean up function and shutdown
    void shutdown();

private:
    // Updates game logic during main loop
    void update();

    // user input
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
