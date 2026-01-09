

#include "proc.hpp"


struct PetStats {
  int hunger{50}, happiness{50}, energy{50}, cleanliness{50};
};


struct PetState {
  PetStats pStats{};
  SystemMetrics sMetrics{};

  bool isAlive{}, isHungry{}, isHappy{}, hasEnergy{}, isClean{};

};
