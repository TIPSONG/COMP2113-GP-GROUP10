#include "Card.h"

Card::Card(CardType type) : type(type) {}

CardType Card::getType() const {
    return type;
}

bool Card::isSpecial() const {
    return type == CardType::REVOLUTION || type == CardType::HARMONY;
}

bool Card::isEquivalentTo(CardType targetType) const {
    switch (type) {
        case CardType::REVOLUTION:
            return true;  // 革命等价于任何牌型
        case CardType::HARMONY:
            return false; // 调和不等价于任何牌型
        default:
            return type == targetType; // 普通牌仅等价于自身
    }
}