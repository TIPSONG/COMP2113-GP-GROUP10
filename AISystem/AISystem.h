#ifndef AISYSTEM_H
#define AISYSTEM_H

#include <string>
#include <vector>
#include "../RoleSystem/Role.h"
#include "../CardSystem/Card.h"
#include "../Difficulty/DifficultyConfig.h"

class AISystem {
public:
    AISystem(DifficultyConfig* difficulty);

    // 决定AI要出的牌
    Card chooseCardToPlay(Role& aiPlayer);

    // 决定AI是否质疑上一个玩家
    bool decideChallenge(Role& aiPlayer, const Role& previousPlayer, const Card& declaredCard);

    // 输出AI的表达内容（根据难度与角色性格）
    std::string outputExpression(const Role& aiPlayer, bool isBluffing);

private:
    DifficultyConfig* difficulty;

    // 内部辅助函数
    bool isForcedChallenge(const Role& aiPlayer, const Role& nextPlayer);
    bool randomDecision(double probability);
};

#endif
