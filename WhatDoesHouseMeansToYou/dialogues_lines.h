#pragma once
#include <string>

struct dialogues_lines
{
public:
    std::string speaker;
    std::string line;

public:
    dialogues_lines() = default;
    dialogues_lines(const std::string& s, const std::string& l);
};