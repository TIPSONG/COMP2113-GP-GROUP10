#ifndef ROLE_H
#define ROLE_H

// 跨文件夹引用 cardsystem 中的头文件
#include "../cardsystem/Card.h"
#include "../cardsystem/Deck.h"
#include <vector>

class Role {
private:
    RoleType type;               // 角色类型（复用 Deck 中定义的 RoleType）
    bool isPlayerControlled;     // 是否玩家控制
    std::vector<Card> handCards; // 手牌

public:
    // 构造函数
    Role(RoleType roleType, bool isPlayer);

    // 获取角色类型
    RoleType getRoleType() const;

    // 判断是否玩家控制
    bool isPlayer() const;

    // 获取手牌
    const std::vector<Card>& getHand() const;

    // 设置手牌（从 cardsystem 发牌后调用）
    void setHand(const std::vector<Card>& newHand);

    // 验证手牌是否符合角色特性（核心查验逻辑）
    bool checkHandValidity() const;

    // 强制质疑判定
    bool isForcedToChallenge(RoleType nextRole) const;
};

#endif // ROLE_H