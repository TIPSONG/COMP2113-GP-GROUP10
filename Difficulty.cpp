#include "Difficulty.h"
#include <cstdlib>  // 用于rand()生成随机数（淘汰概率判定）

// 构造函数：根据难度等级调用对应初始化函数
DifficultyConfig::DifficultyConfig(DifficultyLevel level) : currentLevel(level) {
    switch (level) {
        case DifficultyLevel::Noob:
            initNoobConfig();
            break;
        case DifficultyLevel::Normal:
            initNormalConfig();
            break;
        case DifficultyLevel::Ex:
            initExConfig();
            break;
        case DifficultyLevel::Hard:
            initHardConfig();
            break;
    }
}

// ------------------------------
// 私有方法：各难度参数初始化（严格遵循游戏规则）
// ------------------------------
void DifficultyConfig::initNoobConfig() {
    initialRopeCount = 5;                // 5根绳子
    isLastRopeEliminateOnly = true;      // 仅最后1根绳子触发淘汰
    isExpressionSystemEnabled = true;    // 启用表情系统
    aiLieProbability = 0.0f;             // 全说真话（说谎概率0）
    aiPrioritizeHumanPlayer = false;     // 不优先质疑人类
    isRoleForceChallengeValid = true;    // 角色强制质疑规则生效
}

void DifficultyConfig::initNormalConfig() {
    initialRopeCount = 5;                // 5根绳子
    isLastRopeEliminateOnly = false;     // 正常淘汰（每根绳子概率均等）
    isExpressionSystemEnabled = true;    // 启用表情系统
    aiLieProbability = 0.3f;             // 小概率说谎（30%）
    aiPrioritizeHumanPlayer = true;      // 正常按规则选择目标（此处定义为优先人类）
    isRoleForceChallengeValid = true;    // 角色强制质疑规则生效
}

void DifficultyConfig::initExConfig() {
    initialRopeCount = 3;                // 3根绳子（难度提升）
    isLastRopeEliminateOnly = false;     // 正常淘汰
    isExpressionSystemEnabled = false;   // 不输出表情
    aiLieProbability = 0.4f;             // 小概率说谎（40%，比Normal略高）
    aiPrioritizeHumanPlayer = true;      // 正常按规则选择目标
    isRoleForceChallengeValid = true;    // 角色强制质疑规则生效
}

void DifficultyConfig::initHardConfig() {
    initialRopeCount = 3;                // 3根绳子
    isLastRopeEliminateOnly = false;     // 正常淘汰
    isExpressionSystemEnabled = false;   // 不运行表情系统
    aiLieProbability = 0.0f;             // 表情系统未启用，说谎概率无效
    aiPrioritizeHumanPlayer = true;      // 正常按规则选择目标
    isRoleForceChallengeValid = false;   // 角色强制质疑特性失效（核心难度点）
}

// ------------------------------
// 核心逻辑：根据难度规则判定玩家是否被淘汰
// ------------------------------
bool DifficultyConfig::judgeElimination(int remainingRopes) const {
    // 情况1：Noob难度（仅最后1根绳子被选时淘汰）
    if (isLastRopeEliminateOnly) {
        // remainingRopes=0 表示初始5根绳子已被选完（最后1根被选）
        return remainingRopes == 0;
    }
    // 情况2：Normal/Ex/Hard难度（每根绳子被选时，淘汰概率均等）
    else {
        // 淘汰概率 = 1 / 初始绳子数（符合规则中"每根绳子被选时概率均等淘汰"）
        // 实现逻辑：生成0~(initialRopeCount-1)的随机数，若为0则淘汰
        return (rand() % initialRopeCount) == 0;
    }
}


