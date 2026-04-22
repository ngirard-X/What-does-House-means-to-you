#pragma once
#include <string>
#include <vector>
#include "dialogues_lines.h"
#include "choice.h"

struct Scene
{
    std::string sceneId;
    std::string backgroundPath;
    std::string characterPath;
    std::string musicPath;
    std::string nextSceneId;

    std::vector<dialogues_lines> dialogues;
    std::vector<Choice> choices;

    bool hasChoices = false;
    bool isEnding = false;
};