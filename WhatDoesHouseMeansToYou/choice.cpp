#include "choice.h"

ChoiceBox::ChoiceBox(sf::Font& font)
    : m_font(font), m_visible(false), m_selected(0)
{}

void ChoiceBox::show(const std::vector<Choice>& choices)
{
    m_choices = choices;
    m_visible = true;
    m_selected = 0;

    buildTexts();
}

void ChoiceBox::hide()
{
    m_visible = false;
}

bool ChoiceBox::isVisible() const
{
    return m_visible;
}

void ChoiceBox::handleKey(sf::Keyboard::Key key, std::string& outNext)
{
    if (!m_visible)
    {
        return;
    }

    if (key == sf::Keyboard::Key::Up || key == sf::Keyboard::Key::Z)
    {
        m_selected = (m_selected - 1 + (int)m_choices.size()) % (int)m_choices.size();
    }

    if (key == sf::Keyboard::Key::Down || key == sf::Keyboard::Key::S)
    {
        m_selected = (m_selected + 1) % (int)m_choices.size();
    }

    if (key == sf::Keyboard::Key::Space || key == sf::Keyboard::Key::Enter)
    {
        outNext = m_choices[m_selected].nextScene;

        m_visible = false;
    }

    updateColors();
}

void ChoiceBox::draw(sf::RenderWindow& window)
{
    if (!m_visible)
    {
        return;
	}

    window.draw(m_bg);

    for (auto& t : m_texts)
    {
        window.draw(t);
	}
}

void ChoiceBox::buildTexts()
{
    m_texts.clear();

    float boxW = 600.f;
    float boxH = 60.f + m_choices.size() * 70.f;
    float boxX = 960.f - boxW / 2.f;
    float boxY = 400.f;

    m_bg.setSize({ boxW, boxH });
    m_bg.setPosition({ boxX, boxY });
    m_bg.setFillColor(sf::Color(10, 10, 30, 230));
    m_bg.setOutlineColor(sf::Color(160, 140, 220));
    m_bg.setOutlineThickness(2.f);

    for (int i = 0; i < (int)m_choices.size(); i++)
    {
        sf::Text t(m_font, m_choices[i].label, 34);

        auto lb = t.getLocalBounds();
        t.setOrigin({ lb.position.x + lb.size.x / 2.f, lb.position.y + lb.size.y / 2.f });
        t.setPosition({ 960.f, boxY + 40.f + i * 70.f });

        m_texts.push_back(t);
    }
    updateColors();
}

void ChoiceBox::updateColors()
{
    for (int i = 0; i < (int)m_texts.size(); i++)
    {
        if (i == m_selected)
        {
            m_texts[i].setFillColor(sf::Color(255, 220, 100));
        }
        else
        {
            m_texts[i].setFillColor(sf::Color(180, 160, 220));
        }
    }
}