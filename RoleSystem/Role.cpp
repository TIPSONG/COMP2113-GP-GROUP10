#include "Role.h"
#include <algorithm>

Role::Role(RoleType roleType, bool isPlayer) 
    : type(roleType), isPlayerControlled(isPlayer) {}

RoleType Role::getRoleType() const {
    return type;
}

bool Role::isPlayer() const {
    return isPlayerControlled;
}

const std::vector<Card>& Role::getHand() const {
    return handCards;
}

void Role::setHand(const std::vector<Card>& newHand) {
    handCards = newHand;
}

bool Role::checkHandValidity() const {
    switch (type) {
        case RoleType::CIVIL_REPRESENTATIVE:
            // 民权代表：必须含特殊牌（革命/调和）
            return std::any_of(handCards.begin(), handCards.end(),
                [](const Card& card) { return card.isSpecial(); });
        
        case RoleType::EMPEROR:
            // 帝皇：必须含皇权
            return std::any_of(handCards.begin(), handCards.end(),
                [](const Card& card) { return card.getType() == CardType::ROYAL; });
        
        case RoleType::POPE:
            // 教皇：必须含神权
            return std::any_of(handCards.begin(), handCards.end(),
                [](const Card& card) { return card.getType() == CardType::DIVINE; });
        
        case RoleType::KNIGHT:
            // 骑士：必须含民权
            return std::any_of(handCards.begin(), handCards.end(),
                [](const Card& card) { return card.getType() == CardType::CIVIL; });
        
        default:
            return false;
    }
}

bool Role::isForcedToChallenge(RoleType nextRole) const {
    // 强制质疑规则映射
    switch (type) {
        case RoleType::CIVIL_REPRESENTATIVE: return nextRole == RoleType::KNIGHT;
        case RoleType::EMPEROR: return nextRole == RoleType::POPE;
        case RoleType::POPE: return nextRole == RoleType::CIVIL_REPRESENTATIVE;
        case RoleType::KNIGHT: return nextRole == RoleType::EMPEROR;
        default: return false;
    }
}