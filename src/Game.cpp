#include "Game.hpp"
#include "Input.hpp"
#include "Load_Save.hpp"
#include "Pet.hpp"
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
    state = loadGame();

    // If no save file or pet is dead, create new pet
    if (!state.isAlive) {
        // Reset all stats for new pet
        state.pStats.hunger = 50;
        state.pStats.happiness = 50;
        state.pStats.energy = 50;
        state.pStats.cleanliness = 50;
        state.isAlive = true;
        renderer.pushEvent("New pet created! Take good care of it!");
    } else {
        renderer.pushEvent("Welcome back! Your pet missed you!");
    }
}



void Game::run() {
      using clock = std::chrono::steady_clock;

      auto lastFrame = clock::now();

    //game loop
    while (app.running()) {
        // Start frame timing
        auto frameStart = clock::now();

        float dtSeconds = std::chrono::duration<float>(frameStart - lastFrame).count();
        lastFrame = frameStart;

        app.beginFrame();
        update(dtSeconds);
        handleInput();
        render();
        app.endFrame();

        // frame limiting
        auto frameEnd = std::chrono::steady_clock::now();
        auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(
            frameEnd - frameStart).count();

        if (elapsed < FRAME_DELAY_MS) {
            std::this_thread::sleep_for(
                std::chrono::milliseconds(FRAME_DELAY_MS - elapsed));
        }
    }
}

void Game::update(float dtSeconds) {
    // Read hardware stats (CPU, Memory, Disk, Uptime)
    readHardwareStats(state);
    updatePetFromSystem(state, dtSeconds);
    
    // Store alive state before updating
    bool wasAlive = state.isAlive;
    updateStatusFlags(state);
    
    // Check if pet just died this frame
    if (wasAlive && !state.isAlive) {
        renderer.pushEvent("YOUR PET HAS DIED! Press 'L' to load or 'Q' to quit.");
    }
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
