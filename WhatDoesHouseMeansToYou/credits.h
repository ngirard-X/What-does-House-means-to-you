#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Credits
{
public:
    Credits(sf::Font& font);

    void show(const std::string& endMessage);
    void hide();
    void draw(sf::RenderWindow& window);

    bool isVisible() const;
    bool handleKey(sf::Keyboard::Key key);

private:
    sf::Font& m_font;
    sf::Text m_endLine, m_title, m_dev, m_artist, m_hint;

    bool m_visible;

private:
    void centerText(sf::Text& text, float y);
};