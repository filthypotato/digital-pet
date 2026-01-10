#include <algorithm>
#include "Pet.hpp"

static void clamp(PetStats& s) {
    s.hunger      = std::clamp(s.hunger, 0, 100);
    s.happiness   = std::clamp(s.happiness, 0, 100);
    s.energy      = std::clamp(s.energy, 0, 100);
    s.cleanliness = std::clamp(s.cleanliness, 0, 100);
}

void feedPet(PetState& state) {
    state.pStats.hunger += 15;        // less hungry
    state.pStats.happiness += 2;
    state.pStats.cleanliness -= 1;
    clamp(state.pStats);
}

void playWithPet(PetState& state) {
    state.pStats.happiness += 12;
    state.pStats.energy -= 8;
    state.pStats.hunger -= 5;
    clamp(state.pStats);
}

void sleepPet(PetState& state) {
    state.pStats.energy += 20;
    state.pStats.hunger -= 3;
    clamp(state.pStats);
}

void cleanPet(PetState& state) {
    state.pStats.cleanliness += 20;
    state.pStats.happiness -= 1;
    clamp(state.pStats);
}

