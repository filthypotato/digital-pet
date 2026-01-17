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

struct PetTuning {
  // % of when stats start to decay. 25 = 25%, 38 = 38%, 58 = 58% etc.
  float cpuUsage = 25.0f;
  float diskCleanUsage = 10.0f;
  float memUsage = 45.0f;
  float uptime = 10000.0f;

  // speed of decaying stats
  float energyDecaySec = 3.0f;
  float hungerDecaySec = 4.0f;
  float cleanDecaySec  = 3.0f;
  float happyDecaySec  = 3.0f;

  // when stats drop to a certain level
  int hungerLow{30};
  int happyLow{35};
  int energyLow{25};
  int cleanLow{15};

  int deathCritZeros{2}; // how many stats to hit 0 for pet to die
};

// struct to hold the pets mood
struct PetMood {
    std::string happy{};
    std::string bored{};
    std::string angry{};
    std::string lazy{};
    std::string dirty{};
};

struct PetDebt {
    float energy{};
    float clean{};
    float hunger{};
    float happy{};
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
    PetTuning tuning{};
    PetDebt debt{};

    bool hasPrevCpu{false};
    bool showDebug{false};

    // Status flags (calculated from stats)
    bool isAlive{true};          // Is the pet still alive?
    bool isHungry{false};        // Is hunger below threshold?
    bool isHappy{true};          // Is happiness above threshold?
    bool hasEnergy{true};        // Does pet have energy?
    bool isClean{true};          // Is pet clean enough?


};

// Fwd declarations for pet actions
void feedPet(PetState& state);
void playWithPet(PetState& state);
void sleepPet(PetState& state);
void cleanPet(PetState& state);

// fwd declaration for linking system health to pet needs
void updatePetFromSystem(PetState& state, float dtSeconds);

void updateStatusFlags(PetState& state);
const char* getPetStatusMsg(const PetState& state);


