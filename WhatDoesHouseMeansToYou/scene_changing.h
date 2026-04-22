#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>

struct Dialogue {
public:
    std::string speaker;
    std::string text;
};

struct SceneData {
public:
    std::string id;
    std::string bgPath;
    std::string charPath;
    std::string musicPath;
    std::string nextScene;

    std::vector<Dialogue> dialogues;

    bool isEnd = false;
};

class Scene_changing {
public:
    Scene_changing();

    bool load(const std::string& sceneId, sf::Texture& bgTex, sf::Sprite& bgSprite,
        sf::Texture& charTex, sf::Sprite& charSprite, sf::Text& speaker, sf::Text& dialogue);

    const SceneData* get(const std::string& sceneId) const;

private:
    void buildScenes();

private:
    std::unordered_map<std::string, SceneData> scenes;
};