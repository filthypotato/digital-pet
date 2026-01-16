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
        if (!state.isAlive) {
            renderer.pushEvent("Your pet is dead. Cannot feed.");
            break;
        }
        feedPet(state);
        renderer.pushEvent("You fed your pet!");
        break;

    case 'p':
        if (!state.isAlive) {
            renderer.pushEvent("Your pet is dead. Cannot play.");
            break;
        }
        playWithPet(state);
        renderer.pushEvent("You played with your pet!");
        break;

    case 's':
        if (!state.isAlive) {
            renderer.pushEvent("Your pet is dead. Cannot sleep.");
            break;
        }
        sleepPet(state);
        renderer.pushEvent("Your pet is sleeping...");
        break;

    case 'c':
        if (!state.isAlive) {
            renderer.pushEvent("Your pet is dead. Cannot clean.");
            break;
        }
        cleanPet(state);
        renderer.pushEvent("You cleaned your pet!");
        break;

    case 'l':
        state = loadGame();
        renderer.pushEvent("PetState Loaded! ^_^");
        break;
    case 'd':
        state.showDebug = !state.showDebug;
        break;
}

}


