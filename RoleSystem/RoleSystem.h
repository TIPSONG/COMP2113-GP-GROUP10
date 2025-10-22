#ifndef ROLESYSTEM_H
#define ROLESYSTEM_H

#include "Role.h"
#include "../cardsystem/Deck.h"
#include <iostream>

class RoleSystem {
public:
    // 查验角色手牌是否正确（错误则生成正确手牌）
    void verifyAndFixHand(Role& role, Deck& deck, int expectedHandSize) {
        const auto& hand = role.getHand();
        
        // 检查1：数量是否正确
        bool isCountValid = (hand.size() == expectedHandSize);
        // 检查2：内容是否符合角色特性
        bool isContentValid = role.checkHandValidity();

        // 输出查验结果
        printVerificationResult(role, isCountValid, isContentValid);

        // 若错误，重新发牌并修正
        if (!isCountValid || !isContentValid) {
            std::cout << "→ 正在重新发牌..." << std::endl;
            auto fixedHand = deck.dealForRole(role.getRoleType(), expectedHandSize);
            role.setHand(fixedHand);
            std::cout << "→ 修正后手牌：";
            printHand(fixedHand);
            std::cout << std::endl;
        }
    }

private:
    // 打印牌型辅助函数
    void printCardType(CardType type) const {
        switch (type) {
            case CardType::ROYAL:    std::cout << "皇权"; break;
            case CardType::DIVINE:   std::cout << "神权"; break;
            case CardType::CIVIL:    std::cout << "民权"; break;
            case CardType::REVOLUTION: std::cout << "革命"; break;
            case CardType::HARMONY:  std::cout << "调和"; break;
        }
    }

    // 打印手牌
    void printHand(const std::vector<Card>& hand) const {
        for (const auto& card : hand) {
            printCardType(card.getType());
            std::cout << " ";
        }
    }

    // 打印查验结果
    void printVerificationResult(const Role& role, bool countValid, bool contentValid) const {
        std::cout << "\n=== 角色手牌查验 ===" << std::endl;
        std::cout << "角色：";
        switch (role.getRoleType()) {
            case RoleType::CIVIL_REPRESENTATIVE: std::cout << "民权代表"; break;
            case RoleType::EMPEROR: std::cout << "帝皇"; break;
            case RoleType::POPE: std::cout << "教皇"; break;
            case RoleType::KNIGHT: std::cout << "骑士"; break;
        }
        std::cout << (role.isPlayer() ? "（玩家）" : "（AI）") << std::endl;

        std::cout << "原手牌：";
        printHand(role.getHand());
        std::cout << std::endl;

        if (countValid && contentValid) {
            std::cout << "✅ 发牌正确（数量和内容均符合要求）" << std::endl;
        } else {
            std::cout << "❌ 发牌错误：";
            if (!countValid) std::cout << "数量不符；";
            if (!contentValid) std::cout << "缺少必需牌型；";
            std::cout << std::endl;
        }
    }
};

#endif // ROLESYSTEM_H