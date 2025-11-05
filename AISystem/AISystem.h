#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <vector>
#include "Player.h"
#include "Enemy.h"
#include "Map.h"

class AISystem {
public:
    AISystem() = default;

    void updateAI(Player& player, std::vector<Enemy>& enemies, const Map& map);

private:
    void makeDecision(Enemy& enemy, const Player& player, const Map& map);
    double calcDistance(const Enemy& enemy, const Player& player);
};

#endif
