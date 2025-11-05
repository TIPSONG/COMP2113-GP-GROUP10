#include "AISystem.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

AISystem::AISystem(DifficultyConfig* difficulty)
    : difficulty(difficulty) {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
}

// AI 选择要出的牌
Card AISystem::chooseCardToPlay(Role& aiPlayer) {
    std::vector<Card>& hand = aiPlayer.getHandCards();
    if (hand.empty()) {
        std::cerr << "AI " << aiPlayer.getName() << " has no cards!" << std::endl;
        return Card("Empty", "None");
    }

    // 简单策略：随机出牌（后续可扩展为策略性出牌）
    int index = std::rand() % hand.size();
    Card chosen = hand[index];

    std::cout << "[AI] " << aiPlayer.getName()
              << " chooses to play card: " << chosen.getType() << std::endl;

    return chosen;
}

// 决定是否质疑上一位玩家
bool AISystem::decideChallenge(Role& aiPlayer, const Role& previousPlayer, const Card& declaredCard) {
    // 强制质疑判定
    if (isForcedChallenge(aiPlayer, previousPlayer)) {
        std::cout << "[AI] " << aiPlayer.getName() << " (forced rule) challenges " 
                  << previousPlayer.getName() << "!" << std::endl;
        return true;
    }

    // 难度决定质疑概率
    double baseProbability = difficulty->getChallengeProbability();
    bool decision = randomDecision(baseProbability);

    std::cout << "[AI] " << aiPlayer.getName()
              << (decision ? " decides to challenge " : " does not challenge ")
              << previousPlayer.getName() << std::endl;

    return decision;
}

// 表达系统（说真话/假话/沉默）
std::string AISystem::outputExpression(const Role& aiPlayer, bool isBluffing) {
    if (difficulty->getExpressionMode() == "None") return "";

    double lieChance = difficulty->getLieProbability();
    bool tellTruth = !randomDecision(lieChance);

    if (tellTruth)
        return isBluffing ? "（有点心虚的表情）" : "（自信地点头）";
    else
        return isBluffing ? "（镇定地微笑）" : "（回避视线）";
}

// 判断是否触发“强制质疑”
bool AISystem::isForcedChallenge(const Role& aiPlayer, const Role& nextPlayer) {
    std::string roleA = aiPlayer.getType();
    std::string roleB = nextPlayer.getType();

    return (roleA == "民权代表" && roleB == "骑士") ||
           (roleA == "帝皇" && roleB == "教皇") ||
           (roleA == "教皇" && roleB == "民权代表") ||
           (roleA == "骑士" && roleB == "帝皇");
}

// 随机判定辅助函数
bool AISystem::randomDecision(double probability) {
    return ((std::rand() % 100) / 100.0) < probability;
}
