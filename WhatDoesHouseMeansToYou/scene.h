#include <string>
#include <vector>

#include "dialogues_lines.h"
#include "choice.h"

#pragma once
class scene
{
private:
	std::string sceneId;
	std::string backgroundImageId;
	std::string musicId;

	std::vector<dialogues_lines> dialogues;
	std::vector<choice> choices;
};

