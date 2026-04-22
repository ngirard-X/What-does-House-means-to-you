#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

struct Choice
{
    std::string label;
    std::string nextScene;
};

class ChoiceBox
{
public:
    ChoiceBox(sf::Font& font);

    void show(const std::vector<Choice>& choices);
    void hide();
    void handleKey(sf::Keyboard::Key key, std::string& outNext);
    void draw(sf::RenderWindow& window);

    bool isVisible() const;

private:
    sf::Font& m_font;
    sf::RectangleShape m_bg;

    std::vector<Choice> m_choices;
    std::vector<sf::Text> m_texts;

private:
    bool m_visible;

    int m_selected;

private:
    void buildTexts();
    void updateColors();
};