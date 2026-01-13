#include "Load_Save.hpp"
#include "Input.hpp"
#include "ncurses_app.hpp"
#include "Renderer.hpp"

void keyboardInput(NcursesApp& app, Renderer& renderer, PetState& state) {
// User input
int ch = app.pollInput();  // Gets keyboard input

if (ch == ERR) return;

switch (std::tolower(static_cast<unsigned char>(ch))) {
    case 'q':
        saveGame(state);
        renderer.pushEvent("PetState Saved! Tah Tah!");
        app.stop();
        return;

    case 'f':
        feedPet(state);
        renderer.pushEvent("You fed your pet!");
        break;

    case 'p':
        playWithPet(state);
        renderer.pushEvent("You played with your pet!");
        break;

    case 's':
        sleepPet(state);
        renderer.pushEvent("Your pet is sleeping...");
        break;

    case 'c':
        cleanPet(state);
        renderer.pushEvent("You cleaned your pet!");
        break;

    case 'l':
        state = loadGame();
        renderer.pushEvent("PetState Loaded! ^_^");
        break;
}

}


