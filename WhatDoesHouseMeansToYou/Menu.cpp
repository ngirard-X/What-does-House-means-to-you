#include "menu.h"
#include <cmath>
#include <cstdlib>

Menu::Menu(sf::Font& font)
    : m_font(font), m_time(0.f), m_title(font, "", 90), m_subtitle(font, "", 22), m_prompt(font, "", 26)
{
    srand(42);
    spawnStars(200, 0.5f, 0.25f);
    spawnStars(100, 1.1f, 0.55f);
    spawnStars(40, 2.0f, 0.90f);

    m_title.setString("What does Home\nmeans to you?");
    m_title.setFillColor(sf::Color(240, 234, 255));

    m_subtitle.setString("APPUIYEZ SUR ESPACE POUR COMMENCER");
    m_subtitle.setFillColor(sf::Color(136, 136, 187));
    m_subtitle.setLetterSpacing(3.f);

    m_prompt.setString("Vous incarnez un enquêteur de police tourmenté par une affaire de meurtre dont le coupable est reconnu mais sans motif valable, trouvez ce dernier");
    m_prompt.setFillColor(sf::Color(180, 160, 230));
    m_prompt.setLetterSpacing(1.f);

    m_divider.setSize({ 200.f, 1.f });
    m_divider.setFillColor(sf::Color(123, 108, 170, 180));

    centerAll();
}

void Menu::update(float dt)
{
    m_time += dt;

    float pulse = 0.5f + 0.5f * std::sin(m_time * 2.2f);
    int a = (int)(80 + 170 * pulse);

    m_prompt.setFillColor(sf::Color(180, 160, 230, a));
}

void Menu::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(6, 6, 15));

    drawStars(window);

    window.draw(m_subtitle);
    window.draw(m_title);
    window.draw(m_divider);
    window.draw(m_prompt);
}

void Menu::spawnStars(int count, float radius, float alpha)
{
    for (int i = 0; i < count; i++)
    {
        Star s;

        s.x = (float)(rand() % 1920);
        s.y = (float)(rand() % 1080);
        s.radius = radius * (0.5f + (rand() % 100) / 100.f);
        s.baseAlpha = alpha * (0.4f + (rand() % 60) / 100.f);
        s.twinkle = (rand() % 628) / 100.f;
        s.twinkleSpeed = 0.008f + (rand() % 20) / 1000.f;

        m_stars.push_back(s);
    }
}

void Menu::drawStars(sf::RenderWindow& window)
{
    sf::CircleShape circle;

    for (auto& s : m_stars)
    {
        s.twinkle += s.twinkleSpeed;

        float tw = 0.65f + 0.35f * std::sin(s.twinkle);
        int a = (int)(s.baseAlpha * tw * 255.f);

        circle.setRadius(s.radius);
        circle.setFillColor(sf::Color(210, 200, 255, a));
        circle.setPosition({ s.x - s.radius, s.y - s.radius });

        window.draw(circle);
    }
}

void Menu::centerAll()
{
    auto tb = m_title.getLocalBounds();

    m_title.setOrigin({ tb.position.x + tb.size.x / 2.f, tb.position.y + tb.size.y / 2.f });
    m_title.setPosition({ 960.f, 500.f });

    auto sb = m_subtitle.getLocalBounds();

    m_subtitle.setOrigin({ sb.position.x + sb.size.x / 2.f, 0.f });
    m_subtitle.setPosition({ 960.f, 310.f });

    m_divider.setOrigin({ 100.f, 0.f });
    m_divider.setPosition({ 960.f, 620.f });

    auto pb = m_prompt.getLocalBounds();

    m_prompt.setOrigin({ pb.position.x + pb.size.x / 2.f, 0.f });
    m_prompt.setPosition({ 960.f, 650.f });
}