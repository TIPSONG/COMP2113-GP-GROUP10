#ifndef DECK_H
#define DECK_H

#include "Card.h"
#include <vector>
#include <random>

// 角色类型枚举
enum class Role {
    CIVIL_REPRESENTATIVE,  // 民权代表
    EMPEROR,               // 帝皇
    POPE,                  // 教皇
    KNIGHT                 // 骑士
};

class Deck {
private:
    std::vector<Card> cards;       // 存储牌库
    std::mt19937 rng;              // 随机数生成器

    // 从牌库中抽取指定类型的牌（内部使用）
    bool drawSpecificType(CardType type, Card& card);

public:
    // 构造函数：初始化牌库
    Deck();
    
    // 洗牌
    void shuffle();
    
    // 通用发牌：从牌库顶部发num张牌
    std::vector<Card> deal(int num);
    
    // 针对特定角色的发牌：确保包含角色所需的特定牌型
    std::vector<Card> dealForRole(Role role, int totalNum);
    
    // 获取剩余牌数量
    int remainingCards() const;
};

#endif // DECK_H