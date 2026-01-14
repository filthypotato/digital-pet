#include "Game.hpp"
#include "Input.hpp"
#include "Load_Save.hpp"
#include "proc.hpp"
#include <chrono>
#include <thread>

Game::Game() {}

Game::~Game() {
    shutdown();
}

void Game::init() {

    app.init();
    renderer.init();

    // Load saved game state
    state = loadGame();

    // If no save file or pet is dead, create new pet
    if (!state.isAlive) {
        state.isAlive = true;
        renderer.pushEvent("New pet created! Take good care of it!");
    } else {
        renderer.pushEvent("Welcome back! Your pet missed you!");
    }
}

void Game::run() {

    //game loop
    while (app.running()) {
        // Start frame timing
        auto frameStart = std::chrono::steady_clock::now();

        // Clear screen for new frame
        app.beginFrame();

        // Updates game state
        update();

        // user input
        handleInput();

        // Renders everything
        render();

        // Display current frame
        app.endFrame();

        // Frame rate limiting
        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            frameEnd - frameStart).count();

        if (elapsed < FRAME_DELAY_MS) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(FRAME_DELAY_MS - elapsed));
        }
    }
}

void Game::update() {
    // Read hardware stats (CPU, Memory, Disk, Uptime)
    readHardwareStats(state);

    // TODO: Update pet stats based on system metrics
    // TODO: Apply time-based decay to stats
    // TODO: Update status flags (isHungry, isHappy, etc)
    // TODO: Check if pet is still alive
}

void Game::handleInput() {
    keyboardInput(app, renderer, state);
}

void Game::render() {
    renderer.draw(state);
}

void Game::shutdown() {
    app.shutdown();
}
