#include <iostream>
#include <fstream>
#include "Pet.hpp"

// Function that saves the game state to a binary file
void saveGame(const PetState& state) {
    std::ofstream saveFile("savegame.dat", std::ios::binary);
    if (saveFile.is_open()) {
        saveFile.write(reinterpret_cast<const char*>(&state), sizeof(PetState));
        saveFile.close();
    } else {
        std::cerr << "Unable to open file to make edits!\n";
    }
}

// Function that load the game state from a binary file
PetState loadGame() {
    PetState state;
    std::ifstream loadFile("savegame.dat", std::ios::binary);
    if (loadFile.is_open()) {
        loadFile.read(reinterpret_cast<char*>(&state), sizeof(PetState));
        loadFile.close();
        std::cout << "PetState succesfully loaded!.\n";
    } else {
        std::cerr << "Unable to open file to make edits!.\n";
    }
    return state;
}

