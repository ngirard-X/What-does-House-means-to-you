#include "scene_changing.h"
#include <iostream>

Scene_changing::Scene_changing() 
{
    buildScenes();
}

void Scene_changing::buildScenes() 
{
    // PROLOGUE
    {
        SceneData s;

        s.id = "prologue";
        s.bgPath = "assets/bureauS.png";
        s.charPath = "assets/enqueteur.png";
        s.nextScene = "chapter1";
        s.dialogues = {
            {"Narrateur", "Une ville grise sous une pluie d'automne incessante."},
            {"Narrateur", "Tu reviens après dix ans d'absence."},
            {"Toi", "Pourquoi suis-je revenu ici ?"},
            {"Narrateur", "Une lettre anonyme : « Reviens. Tout brûle. »"}
        };

        scenes["prologue"] = s;
    }

    // CHAPITRE 1 - métro
    {
        SceneData s;

        s.id = "chapter1";
        s.bgPath = "assets/metro.png";
        s.charPath = "assets/enqueteur.png";
        s.nextScene = "chapter2";
        s.dialogues = {
            {"Toi", "Cette gare... rien n'a changé."},
            {"Narrateur", "Les mêmes tuiles cassées, la même odeur de diesel."},
            {"Toi", "Mais la ville semble... différente."},
            {"Narrateur", "Quelque chose de grave s'est passé."}
        };

        scenes["chapter1"] = s;
    }

    // CHAPITRE 2 - Ville
    {
        SceneData s;

        s.id = "chapter2";
        s.bgPath = "assets/ville.png";
        s.charPath = "assets/enqueteur.png";
        s.nextScene = "chapter3";
        s.dialogues = {
            {"Narrateur", "Dans la rue, un vieil homme trébuche sous la pluie."},
            {"Toi", "Je n'ai pas le temps de m'arrêter..."},
            {"Vieil Homme", "Merci quand même, jeune homme... Marie parlait de toi."},
            {"Toi", "Marie ? Ma mère ?"}
        };

        scenes["chapter2"] = s;
    }

    // CHAPITRE 3 - Prison
    {
        SceneData s;

        s.id = "chapter3";
        s.bgPath = "assets/prison.png";
        s.charPath = "assets/prisonniere_prison.png";
        s.nextScene = "chapter4";
        s.dialogues = {
            {"Narrateur", "Ton quartier d'enfance est méconnaissable."},
            {"Toi", "Les immeubles à moitié démolis..."},
            {"Narrateur", "La « rénovation urbaine » a tout rasé."},
            {"Toi", "Et la maison de maman ?"}
        };

        scenes["chapter3"] = s;
    }

    // CHAPITRE 4 - Entree
    {
        SceneData s;

        s.id = "chapter4";
        s.bgPath = "assets/entree.png";
        s.charPath = "assets/prisonniere.png";
        s.nextScene = "chapter5";
        s.dialogues = {
            {"Homme Masqué", "Le promoteur brûle tout pour ses tours de luxe."},
            {"Homme Masqué", "J'ai les preuves, mais personne n'ose parler."},
            {"Toi", "Pourquoi me le dire à moi ?"},
            {"Homme Masqué", "Parce que tu es le fils de Marie."}
        };

        scenes["chapter4"] = s;
    }

    // CHAPITRE 5 - Salon
    {
        SceneData s;

        s.id = "chapter5";
        s.bgPath = "assets/salon.png";
        s.charPath = "assets/prisonniere.png";
        s.nextScene = "chapter6";
        s.dialogues = {
            {"Narrateur", "La maison de ton enfance est encore debout... à peine."},
            {"Toi", "Maman..."},
            {"Narrateur", "Sur la table, sa dernière lettre."},
            {"Maman", "« Je t'attendrai toujours. Ici, c'est chez toi. »"}
        };

        scenes["chapter5"] = s;
    }

    // CHAPITRE 6 - Chambre
    {
        SceneData s;

        s.id = "chapter6";
        s.bgPath = "assets/chambre.png";
        s.charPath = "assets/prisonniere.png";
        s.nextScene = "chapter7";
        s.dialogues = {
            {"Narrateur", "Le train de nuit part dans une heure."},
            {"Toi", "Est-ce que cette ville peut encore être ma maison ?"},
            {"Narrateur", "Les cendres de ton passé fument encore."},
            {"Toi", "Je reste. Pour elle."}
        };

        scenes["chapter6"] = s;
    }

    // CHAPITRE 7 - Credits
    {
        SceneData s;

        s.id = "chapter7";
        s.bgPath = "assets/aube.png";
        s.charPath = "assets/char_hero.png";
        s.nextScene = "";
        s.isEnd = true;
        s.dialogues = {
            {"Narrateur", "L'aube se lève sur la ville blessée."},
            {"Toi", "Tout ce chemin pour comprendre ce que « maison » voulait dire."},
            {"Narrateur", "La maison, c'est là où ton cœur reste."},
            {"Toi", "Ici. Pour toujours."},
            {"Narrateur", "FIN"}
        };

        scenes["chapter7"] = s;
    }
}

bool Scene_changing::load(const std::string& sceneId, sf::Texture& bgTex, sf::Sprite& bgSprite,
    sf::Texture& charTex, sf::Sprite& charSprite, sf::Text& speaker, sf::Text& dialogue) 
{

    auto it = scenes.find(sceneId);

    if (it == scenes.end()) 
    {
        std::cerr << "Scène introuvable: " << sceneId << "\n";

        return false;
    }

    const SceneData& scene = it->second;

    if (!scene.bgPath.empty() && bgTex.loadFromFile(scene.bgPath)) 
    {
        bgSprite.setTexture(bgTex);
        bgSprite.setScale({1920.f / bgTex.getSize().x, 1080.f / bgTex.getSize().y});
    }

    if (!scene.charPath.empty() && charTex.loadFromFile(scene.charPath)) 
    {
        charSprite.setTexture(charTex);

        float scale = 750.f / charTex.getSize().y;

        charSprite.setScale({scale, scale});
    }

    if (!scene.dialogues.empty()) 
    {
        speaker.setString(scene.dialogues[0].speaker);
        dialogue.setString(scene.dialogues[0].text);
    }

    return true;
}

const SceneData* Scene_changing::get(const std::string& sceneId) const 
{
    auto it = scenes.find(sceneId);

    return it != scenes.end() ? &it->second : nullptr;
}