#pragma once
#include <functional>
#include <memory>
#include <vector>

enum class BTStatus
{
    Success,
    Failure,
    Running
};

struct BTNode
{
    virtual BTStatus tick() = 0;
    virtual ~BTNode() = default;
};

struct BTCondition : BTNode
{
    std::function<bool()> condition;
    explicit BTCondition(std::function<bool()> c);
    BTStatus tick() override;
};

struct BTAction : BTNode
{
    std::function<BTStatus()> action;
    explicit BTAction(std::function<BTStatus()> a);
    BTStatus tick() override;
};

struct BTSequence : BTNode
{
    std::vector<std::shared_ptr<BTNode>> children;
    BTStatus tick() override;
};

struct BTSelector : BTNode
{
    std::vector<std::shared_ptr<BTNode>> children;
    BTStatus tick() override;
};