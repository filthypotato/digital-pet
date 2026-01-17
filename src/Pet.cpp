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

// function to link system health to pet needs
void updatePetFromSystem(PetState& state, float dtSeconds) {
    auto& t = state.tuning;
    auto& d = state.debt;

    if (state.sMetrics.cpuPet > t.cpuUsage)
        d.energy += (1.0f / t.energyDecaySec) * dtSeconds;

    if (state.sMetrics.diskPet > t.diskCleanUsage)
        d.clean += (1.0f / t.cleanDecaySec) * dtSeconds;

    if (state.sMetrics.memPet > t.memUsage)
        d.hunger += (1.0f / t.hungerDecaySec) * dtSeconds;

    if (state.sMetrics.uptimePet > t.uptime)
        d.happy += (1.0f / t.energyDecaySec) * dtSeconds;


    const int e = static_cast<int>(d.energy);
    const int c = static_cast<int>(d.clean);
    const int h = static_cast<int>(d.hunger);
    const int ha = static_cast<int>(d.happy);

    if (e > 0) {
      state.pStats.energy -= e;
      d.energy -= e;
    }
    if (c > 0) {
      state.pStats.cleanliness -= c;
      d.clean -= c;
    }
    if (h > 0) {
      state.pStats.hunger -= h;
      d.hunger -= h;
    }
    if (ha > 0) {
        state.pStats.happiness -= ha;
        d.happy -= ha;
    }

    // Clamp stats after decay to ensure they stay in valid range
    clamp(state.pStats);

}

void updateStatusFlags(PetState& state) {
   const auto& t = state.tuning;

    clamp(state.pStats);

    // how many critcal stats are at 0?
    int critical =
        (state.pStats.hunger == 0) +
        (state.pStats.energy == 0) +
        (state.pStats.happiness == 0) +
        (state.pStats.cleanliness == 0);

    // Pet dies when 2 stats hit 0
    state.isAlive  = (critical < t.deathCritZeros);

    // Update other status flags
    state.isHungry = (state.pStats.hunger <= t.hungerLow);
    state.isHappy  = (state.pStats.happiness >= t.happyLow);
    state.hasEnergy= (state.pStats.energy >= t.energyLow);
    state.isClean  = (state.pStats.cleanliness >= t.cleanLow);
}


const char* getPetStatusMsg(const PetState& state) {
    if (!state.isAlive)
        return "i am deceased boss! D: ";
    if (!state.isClean)
        return "Not feeling so good boss... BATH MEEE!";
    if (!state.hasEnergy)
        return "Gimme some Zzzzz's boss";
    if (state.isHungry)
        return "SUSTANANCE PLZZZZ";
    if (!state.isHappy)
        return "I could use a friend...";

    return "Doing better than most potties :)(petbot lol)"; // (pet bot) lol
}


