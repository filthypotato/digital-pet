#include <algorithm>
#include "Pet.hpp"

// clamps stats to avoid going under 0 or passed 100
static void clamp(PetStats& s) {
    s.hunger      = std::clamp(s.hunger, 0, 100);
    s.happiness   = std::clamp(s.happiness, 0, 100);
    s.energy      = std::clamp(s.energy, 0, 100);
    s.cleanliness = std::clamp(s.cleanliness, 0, 100);
}

void feedPet(PetState& state) {
    state.pStats.hunger += 15;        // increases hunger meter
    clamp(state.pStats);    // clamp the stats
}

void playWithPet(PetState& state) {
    state.pStats.happiness += 12;   // Increases happiness
    clamp(state.pStats);          // clamps the stats
}

void sleepPet(PetState& state) {
    state.pStats.energy += 20;      // Increases engery
    clamp(state.pStats);          // clamps the stats
}

void cleanPet(PetState& state) {
    state.pStats.cleanliness += 20; // Increases cleanliness
    clamp(state.pStats);        // clamps the stats
}

