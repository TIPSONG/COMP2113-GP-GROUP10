#ifndef CARD_H
#define CARD_H

// 牌型枚举
enum class CardType {
    ROYAL,       // 皇权
    DIVINE,      // 神权
    CIVIL,       // 民权
    REVOLUTION,  // 革命（特殊牌）
    HARMONY      // 调和（特殊牌）
};

class Card {
private:
    CardType type;

public:
    // 构造函数
    Card(CardType type);
    
    // 获取牌型
    CardType getType() const;
    
    // 判断是否为特殊牌（革命或调和）
    bool isSpecial() const;
    
    // 等价性判定：当前牌是否等价于目标牌型
    // 革命等价于任何牌型，调和不等价于任何牌型
    bool isEquivalentTo(CardType targetType) const;
};

#endif // CARD_H