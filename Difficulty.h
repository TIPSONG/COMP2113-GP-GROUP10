#ifndef DIFFICULTY_H
#define DIFFICULTY_H

// 难度等级枚举：对应游戏规则中的4个难度
enum class DifficultyLevel {
    Noob,    // 新手难度
    Normal,  // 普通难度
    Ex,      // 专家难度
    Hard     // 困难难度
};

// 难度配置类：封装不同难度的所有差异化规则，提供对外查询接口
class DifficultyConfig {
private:
    // 1. 难度核心参数（根据规则初始化）
    DifficultyLevel currentLevel;       // 当前难度等级
    int initialRopeCount;               // 绞刑架初始绳子数量
    bool isLastRopeEliminateOnly;       // 是否仅最后1根绳子触发淘汰（仅Noob用）
    bool isExpressionSystemEnabled;     // 是否启用AI表情系统
    float aiLieProbability;             // AI表达系统说谎概率（0.0~1.0，Noob/Hard无效）
    bool aiPrioritizeHumanPlayer;       // AI是否优先质疑人类玩家
    bool isRoleForceChallengeValid;     // 角色"强制质疑"规则是否生效（Hard难度失效）

    // 工具函数：初始化不同难度的参数（私有，仅构造函数调用）
    void initNoobConfig();
    void initNormalConfig();
    void initExConfig();
    void initHardConfig();

public:
    // 构造函数：根据传入的难度等级初始化所有参数
    explicit DifficultyConfig(DifficultyLevel level);

    // 2. 参数查询接口（供外部模块调用，只读）
    // 获取当前难度等级
    DifficultyLevel getCurrentLevel() const { return currentLevel; }
    // 获取绞刑架初始绳子数
    int getInitialRopeCount() const { return initialRopeCount; }
    // 判断是否启用表情系统
    bool isExpressionEnabled() const { return isExpressionSystemEnabled; }
    // 获取AI说谎概率（仅Normal/Ex有效）
    float getAiLieProbability() const { return aiLieProbability; }
    // 判断AI是否优先质疑人类
    bool isAiPrioritizeHuman() const { return aiPrioritizeHumanPlayer; }
    // 判断角色"强制质疑"规则是否生效
    bool isForceChallengeValid() const { return isRoleForceChallengeValid; }

    // 3. 核心逻辑接口：根据难度规则判定是否淘汰玩家
    // 参数：触发绞刑后剩余的绳子数（初始绳子数 - 已选绳子数）
    // 返回值：true=淘汰，false=未淘汰
    bool judgeElimination(int remainingRopes) const;
};

#endif // DIFFICULTY_H


