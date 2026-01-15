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

const float cpuUsageToAffectEngery{30};
const float diskUsageToAffectCleanliness{10};
const float memUsageToAffectCleanliness{25};
constexpr float ENERY_DECAY{1.5f};  // loses 1 tick of energy every 1.5 seconds
constexpr float HUNGER_DECAY{2.0f}; // loses 1 tick of hunger every 2 seconds
constexpr float CLEAN_DECAY{3.0f};  // loses 1 tick of cleanliness every 3 seconds
                                    //
// function to link system health to pet needs
void updatePetFromSystem(PetState& state, float dtSeconds) {
    static float energyDebt{};
    static float cleanDebt{};
    static float hungerDebt{};

    // subtract whole numbers from pets stats at the correct speed with fractional decay
    if (state.sMetrics.cpuPet > cpuUsageToAffectEngery)
        energyDebt += (1.0f / ENERY_DECAY) * dtSeconds; // divide 1.0f by decay * dtSeconds
                                          // no decay unless thresholds are bad
    if (state.sMetrics.diskPet < diskUsageToAffectCleanliness)
        cleanDebt += (1.0f / CLEAN_DECAY) * dtSeconds; // divide 1.0f by decay * dtSeconds

    if (state.sMetrics.memPet > memUsageToAffectCleanliness)
        hungerDebt += (1.0f / HUNGER_DECAY) * dtSeconds; // divide 1.0f by decay * dtSeconds

    int e = static_cast<int>(energyDebt);
    int c = static_cast<int>(cleanDebt);
    int h = static_cast<int>(hungerDebt);

    if (e > 0) {
      state.pStats.energy -= e;
      energyDebt -= e;
    }
    if (c > 0) {
      state.pStats.cleanliness -= c;
      cleanDebt -= c;
    }
    if (h > 0) {
      state.pStats.hunger -= h;
      hungerDebt -= h;
    }

    clamp(state.pStats);
}


void updateStatusFlags(PetState& state) {
    constexpr int HUNGER_LOW{30};
    constexpr int HAPPY_LOW{35};
    constexpr int ENERGY_LOW{25};
    constexpr int CLEAN_LOW{15};

    state.isHungry = (state.pStats.hunger <= HUNGER_LOW);

    state.isHappy   = (state.pStats.happiness >= HAPPY_LOW);
    state.hasEnergy = (state.pStats.energy >= ENERGY_LOW);
    state.isClean   = (state.pStats.cleanliness >= CLEAN_LOW);

    int critical = 0;
    if (state.pStats.hunger <= 0)      critical++;
    if (state.pStats.energy <= 0)      critical++;
    if (state.pStats.cleanliness <= 0) critical++;
    if (state.pStats.happiness <= 0)   critical++;

    state.isAlive = (critical < 2);
}

const char* getPetStatusMsg(const PetState& state) {
    if (!state.isAlive)    return "i am deceased boss! D: ";

    if (!state.isClean)    return "Not feeling so good boss... BATH MEEE!";
    if (!state.hasEnergy)  return "Gimme some Zzzzz's boss";
    if (state.isHungry)    return "SUSTANANCE PLZZZZ";
    if (!state.isHappy)    return "I could use a friend...";

    return "Doing better than most bots :)";
}

