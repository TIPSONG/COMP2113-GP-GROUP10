#include "Card.h"
#include "Deck.h"
#include <iostream>

// 打印牌型辅助函数
void printCardType(CardType type) {
    switch (type) {
        case CardType::ROYAL:    std::cout << "皇权"; break;
        case CardType::DIVINE:   std::cout << "神权"; break;
        case CardType::CIVIL:    std::cout << "民权"; break;
        case CardType::REVOLUTION: std::cout << "革命"; break;
        case CardType::HARMONY:  std::cout << "调和"; break;
    }
}

// 测试特殊牌判定逻辑
void testSpecialCards() {
    std::cout << "=== 特殊牌判定测试 ===" << std::endl;
    Card revolution(CardType::REVOLUTION);
    Card harmony(CardType::HARMONY);
    Card royal(CardType::ROYAL);

    std::cout << "革命 vs 皇权: " << (revolution.isEquivalentTo(CardType::ROYAL) ? "等价" : "不等价") << std::endl;
    std::cout << "革命 vs 神权: " << (revolution.isEquivalentTo(CardType::DIVINE) ? "等价" : "不等价") << std::endl;
    std::cout << "调和 vs 皇权: " << (harmony.isEquivalentTo(CardType::ROYAL) ? "等价" : "不等价") << std::endl;
    std::cout << "皇权 vs 皇权: " << (royal.isEquivalentTo(CardType::ROYAL) ? "等价" : "不等价") << std::endl;
}

// 测试发牌功能
void testDealing() {
    std::cout << "\n=== 发牌功能测试 ===" << std::endl;
    Deck deck;
    deck.shuffle();

    // 测试各角色发牌
    auto emperorHand = deck.dealForRole(Role::EMPEROR, 8);
    std::cout << "帝皇手牌（应含皇权）: ";
    for (const auto& card : emperorHand) {
        printCardType(card.getType());
        std::cout << " ";
    }

    auto civilRepHand = deck.dealForRole(Role::CIVIL_REPRESENTATIVE, 8);
    std::cout << "\n民权代表手牌（应含特殊牌）: ";
    for (const auto& card : civilRepHand) {
        printCardType(card.getType());
        std::cout << " ";
    }

    std::cout << "\n剩余牌数量: " << deck.remainingCards() << std::endl;
}

int main() {
    testSpecialCards();
    testDealing();
    return 0;
}