// Pet.hpp
// Data structures for the virtual pet's state
#pragma once

#include "proc.hpp"

// The pet's needs (like a real Tamagotchi)
// Values range from 0-100 (100 is best)
struct PetStats {
    int hunger{25};       // How hungry the pet is (lower = more hungry)
    int happiness{26};    // How happy the pet is
    int energy{23};       // How much energy the pet has
    int cleanliness{12};  // How clean the pet is
};



// struct to hold the pets mood
struct PetMood {
    std::string happy{};
    std::string bored{};
    std::string angry{};
    std::string lazy{};
    std::string dity{};
};

// Complete state of the pet
struct PetState {
    PetStats pStats{};           // The pet's current needs
    SystemMetrics sMetrics{};    // Current system metrics
    CpuTimes cpuOut{};
    MemInfo memOut{};
    CpuTimes prevCpu{};
    PetMood mood{};
    DiskInfo diskOut{};
    UptimeInfo uptimeOut{};

    bool hasPrevCpu{false};

    // Status flags (calculated from stats)
    bool isAlive{true};          // Is the pet still alive?
    bool isHungry{false};        // Is hunger below threshold?
    bool isHappy{true};          // Is happiness above threshold?
    bool hasEnergy{true};        // Does pet have energy?
    bool isClean{true};          // Is pet clean enough?


};

// Basic pet actions
void feedPet(PetState& state);
void playWithPet(PetState& state);
void sleepPet(PetState& state);
void cleanPet(PetState& state);





// TODO: Add function to update pet stats based on system metrics
//       - high CPU usage makes pet tired (lowers energy)
//       - low disk space makes pet dirty (lowers cleanliness)
//       - high memory usage makes pet hungry (lowers hunger stat)

// TODO: Add function to apply time-based decay to stats
//       All stats should slowly decrease over time
//       Use a decayStats(PetState& state, float deltaTime) function

// TODO: Add function to update status flags (isHungry, isHappy, etc)
//       Based on current stat values and thresholds
//       - isHungry = (hunger < 30)

// TODO: Add function to check if pet is dead
//       - isDead = (hunger < 5 && energy < 5) || allStatsBelow10

