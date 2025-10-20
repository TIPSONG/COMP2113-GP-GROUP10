#include "Deck.h"
#include <chrono>
#include <algorithm>

Deck::Deck() {
    // 初始化随机数生成器（使用当前时间作为种子）
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    rng.seed(seed);

    // 初始化牌库：10皇权 + 10神权 + 10民权 + 1革命 + 1调和
    for (int i = 0; i < 10; ++i) {
        cards.emplace_back(CardType::ROYAL);
        cards.emplace_back(CardType::DIVINE);
        cards.emplace_back(CardType::CIVIL);
    }
    cards.emplace_back(CardType::REVOLUTION);
    cards.emplace_back(CardType::HARMONY);
}

void Deck::shuffle() {
    std::shuffle(cards.begin(), cards.end(), rng);
}

std::vector<Card> Deck::deal(int num) {
    std::vector<Card> dealtCards;
    num = std::min(num, (int)cards.size());  // 防止超界

    for (int i = 0; i < num; ++i) {
        dealtCards.push_back(cards.back());
        cards.pop_back();
    }

    return dealtCards;
}

bool Deck::drawSpecificType(CardType type, Card& card) {
    for (auto it = cards.begin(); it != cards.end(); ++it) {
        if (it->getType() == type) {
            card = *it;
            cards.erase(it);
            return true;
        }
    }
    return false;  // 未找到指定类型的牌
}

std::vector<Card> Deck::dealForRole(Role role, int totalNum) {
    std::vector<Card> hand;
    Card requiredCard(CardType::ROYAL);  // 临时初始化
    bool hasRequired = false;

    // 根据角色抽取必须的牌
    switch (role) {
        case Role::CIVIL_REPRESENTATIVE:
            // 民权代表：必含1张特殊牌（优先革命，其次调和）
            if (!drawSpecificType(CardType::REVOLUTION, requiredCard)) {
                hasRequired = drawSpecificType(CardType::HARMONY, requiredCard);
            } else {
                hasRequired = true;
            }
            break;
        case Role::EMPEROR:
            // 帝皇：必含1张皇权
            hasRequired = drawSpecificType(CardType::ROYAL, requiredCard);
            break;
        case Role::POPE:
            // 教皇：必含1张神权
            hasRequired = drawSpecificType(CardType::DIVINE, requiredCard);
            break;
        case Role::KNIGHT:
            // 骑士：必含1张民权
            hasRequired = drawSpecificType(CardType::CIVIL, requiredCard);
            break;
    }

    // 如果成功获取必要牌，补充剩余牌
    if (hasRequired) {
        hand.push_back(requiredCard);
        int remaining = totalNum - 1;
        if (remaining > 0) {
            auto additional = deal(remaining);
            hand.insert(hand.end(), additional.begin(), additional.end());
        }
    }

    return hand;
}

int Deck::remainingCards() const {
    return cards.size();
}
