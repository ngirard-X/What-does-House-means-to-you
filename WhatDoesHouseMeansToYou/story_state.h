#pragma once
#include <string>

struct StoryState
{
public:
    bool helpedOldMan = false;
    bool denounced = false;
    bool stayedInTown = false;

    void reset();

    std::string computeEnding() const;
};