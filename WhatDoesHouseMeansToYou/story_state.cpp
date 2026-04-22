#include "story_state.h"

void StoryState::reset()
{
    helpedOldMan = false;
    denounced = false;
    stayedInTown = false;
}

std::string StoryState::computeEnding() const
{
    int score = (helpedOldMan ? 1 : 0) + (denounced ? 1 : 0) + (stayedInTown ? 1 : 0);

    if (score == 3) return "ending_good";
    if (score == 0) return "ending_bad";

    return "ending_neutral";
}