#include "behavior_tree.h"

BTCondition::BTCondition(std::function<bool()> c)
    : condition(c)
{}

BTStatus BTCondition::tick()
{
    return condition() ? BTStatus::Success : BTStatus::Failure;
}

BTAction::BTAction(std::function<BTStatus()> a)
    : action(a)
{}

BTStatus BTAction::tick()
{
    return action();
}

BTStatus BTSequence::tick()
{
    for (auto& c : children)
    {
        auto s = c->tick();
        if (s != BTStatus::Success)
        {
            return s;
        }
    }
    return BTStatus::Success;
}

BTStatus BTSelector::tick()
{
    for (auto& c : children)
    {
        auto s = c->tick();
        if (s == BTStatus::Success)
        {
            return s;
        }
    }
    return BTStatus::Failure;
}