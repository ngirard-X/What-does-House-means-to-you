#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

struct Star
{
    float x, y;
    float radius;
    float baseAlpha;
    float twinkle;
    float twinkleSpeed;
};

class Menu
{
public:
    Menu(sf::Font& font);

    void update(float dt);
    void draw(sf::RenderWindow& window);

private:
    float m_time;

    sf::Text m_title, m_subtitle, m_prompt;
    sf::RectangleShape m_divider;
    sf::Font& m_font;

    std::vector<Star> m_stars;

private:
    void spawnStars(int count, float radius, float alpha);
    void drawStars(sf::RenderWindow& window);
    void centerAll();
};