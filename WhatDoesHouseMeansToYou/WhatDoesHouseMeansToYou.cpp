#include <iostream>

#include "scene_changing.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "What does home means to you");
    window.setFramerateLimit(120);

    sf::Texture texture;
    if (!texture.loadFromFile("assets/bureauS.png"))
    {
        std::cerr << "Erreur: impossible de charger l'image\n";
        return 0;
    }

    sf::Sprite sprite(texture);
    sprite.setTexture(texture);
    sprite.setPosition({sf::Vector2f(0.f, 0.f)});

    scene_changing changer;
    sf::Texture bgTexture;
    sf::Sprite bg(bgTexture);
    sf::Music music;
    sf::Font font;
    sf::Text dialogue(font);

    changer.changeScene("prologue1", bgTexture, bg, music, dialogue);

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
        }

        window.draw(sprite);
        window.display();
    }

    return 1;
}