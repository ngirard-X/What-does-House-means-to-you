#include "credits.h"

Credits::Credits(sf::Font& font)
    : m_font(font), m_visible(false), m_endLine(font, "", 30), m_title(font, "- Credits -", 42), m_dev(font, "Developpeur : Nolhan Girard", 32),
    m_artist(font, "Artiste : Lia", 32), m_hint(font, "Ce jeu avait pour but de dénoncer ces violences qui ne sont pas punies; Appuyez sur ESPACE pour retourner au menu", 24)
{
    m_title.setFillColor(sf::Color(240, 220, 255));
    centerText(m_title, 350.f);

    m_dev.setFillColor(sf::Color(200, 180, 240));
    centerText(m_dev, 460.f);

    m_artist.setFillColor(sf::Color(200, 180, 240));
    centerText(m_artist, 530.f);

    m_hint.setFillColor(sf::Color(140, 120, 180));
    centerText(m_hint, 680.f);

    m_endLine.setFillColor(sf::Color(255, 220, 150));
    centerText(m_endLine, 260.f);
}

void Credits::centerText(sf::Text& text, float y)
{
    auto b = text.getLocalBounds();

    text.setOrigin({ b.position.x + b.size.x / 2.f, b.position.y + b.size.y / 2.f });
    text.setPosition({ 960.f, y });
}

void Credits::show(const std::string& endMessage)
{
    m_visible = true;
    m_endLine.setString(endMessage);

    centerText(m_endLine, 260.f);
}

void Credits::hide()
{
    m_visible = false;
}

bool Credits::isVisible() const
{
    return m_visible;
}

bool Credits::handleKey(sf::Keyboard::Key key)
{
    if (!m_visible)
    {
        return false;
	}

    if (key == sf::Keyboard::Key::Space)
    {
        m_visible = false;
        return true;
    }
    return false;
}

void Credits::draw(sf::RenderWindow& window)
{
    if (!m_visible)
    {
        return;
    }

    window.clear(sf::Color(6, 6, 15));
    window.draw(m_endLine);
    window.draw(m_title);
    window.draw(m_dev);
    window.draw(m_artist);
    window.draw(m_hint);
}