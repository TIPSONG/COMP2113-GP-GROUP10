#include "cardsystem/Deck.h"
#include "RoleSystem/Role.h"
#include "RoleSystem/RoleSystem.h"
#include <iostream>

int main() {
    // 1. 初始化牌库并洗牌
    Deck gameDeck;
    gameDeck.shuffle();
    std::cout << "初始牌库大小：" << gameDeck.remainingCards() << "张" << std::endl;

    // 2. 创建角色（玩家控制民权代表，AI控制其他角色）
    Role civilRep(RoleType::CIVIL_REPRESENTATIVE, true);   // 玩家
    Role emperor(RoleType::EMPEROR, false);                // AI
    Role pope(RoleType::POPE, false);                      // AI
    Role knight(RoleType::KNIGHT, false);                  // AI

    // 3. 从牌库发牌（8张/人）
    civilRep.setHand(gameDeck.dealForRole(RoleType::CIVIL_REPRESENTATIVE, 8));
    emperor.setHand(gameDeck.dealForRole(RoleType::EMPEROR, 8));
    pope.setHand(gameDeck.dealForRole(RoleType::POPE, 8));
    knight.setHand(gameDeck.dealForRole(RoleType::KNIGHT, 8));

    // 4. 用 RoleSystem 查验并修正手牌
    RoleSystem roleSystem;
    roleSystem.verifyAndFixHand(civilRep, gameDeck, 8);
    roleSystem.verifyAndFixHand(emperor, gameDeck, 8);
    roleSystem.verifyAndFixHand(pope, gameDeck, 8);
    roleSystem.verifyAndFixHand(knight, gameDeck, 8);

    // 5. 测试强制质疑逻辑
    std::cout << "\n=== 强制质疑测试 ===" << std::endl;
    std::cout << "民权代表对骑士是否强制质疑：" 
              << (civilRep.isForcedToChallenge(knight.getRoleType()) ? "是" : "否") << std::endl;
    std::cout << "骑士对帝皇是否强制质疑：" 
              << (knight.isForcedToChallenge(emperor.getRoleType()) ? "是" : "否") << std::endl;

    return 0;
}

