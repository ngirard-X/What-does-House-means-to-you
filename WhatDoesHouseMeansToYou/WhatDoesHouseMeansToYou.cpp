#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <memory>
#include "menu.h"
#include "choice.h"
#include "credits.h"
#include "behavior_tree.h"

struct Scene {
    std::string bg;
    std::string chara;
    std::string next;

    std::vector<std::pair<std::string, std::string>> dialogues;

    bool isEnd = false;
    bool hasChoice = false;
    bool hasFinalChoice = false;
};

int main() 
{
    sf::RenderWindow window(sf::VideoMode({ 1920, 1080 }), "What Does Home Means To You?");
    window.setFramerateLimit(60);

    sf::Font font;

    if (!font.openFromFile("assets/arial.ttf")) 
    {
        std::cerr << "erreur font\n";
        return 1;
    }

    std::map<std::string, Scene> scenes;

    scenes["prologue"] = {
    "assets/bureauS.png", "assets/enqueteur.png", "ch1",
    {
        {"Enquêteur", "C'est pas possible, déjà 4 ans que je réfléchis et rien."},
        {"Enquêteur", "Pas même un indice, pas une seule piste."},
        {"Enquêteur", "Une coupable toute désignée, la piste est sûre, mais aucun motif ni aucune preuve d'une quelconque raison."},
        {"Enquêteur", "Je n'ai plus d'autres choix que d'aller voir la première concernée."},
        {"Enquêteur", "J'ai, de toutes manières, toujours eu envie de la rencontrer."},
    }
    };

    scenes["ch1"] = {
        "assets/metro.png", "assets/enqueteur.png", "ch2",
        {
            {"Narrateur", "*bruits de métro et de foule*"},
            {"Enquêteur", "Toujours aussi bondé, pour mon plus grand désespoir."},
            {"Enquêteur", "Je devrais me dépêcher de sortir d'ici, sinon je vais mourir par suffocation."},
        }
    };

    scenes["ch2"] = {
        "assets/ville.png", "assets/sdf.png", "ch3",
        {
            {"Enquêteur", "Vieil homme dans la rue : on dirait qu'il souhaite me parler."},
            {"Vieil Homme", "Bonsoir jeune homme, aurais-tu une pièce pour moi ?"},
            {"Enquêteur", "Navré, je n'ai rien, je n'ai pas pris mon portefeuille."},
            {"Vieil Homme", "Ce n'est rien, mais rends-moi un service, alors."},
            {"Enquêteur", "Lequel ? Je n'ai vraiment rien sur moi, pas même à manger."},
            {"Vieil Homme", "Ça, j'ai bien compris, je ne suis pas sénile, tout de même."},
            {"Narrateur", "*dit-il en souriant*"},
            {"Vieil Homme", "Non, plus sérieusement, je souhaite que, quels que soient tes choix dans le futur, tu penses à prendre le temps."},
            {"Vieil Homme", "Des mauvais choix peuvent mener à de mauvaises surprises, aussi sache que les gens ont souvent leurs raisons."},
            {"Vieil Homme", "Bon, peu importe, tu ne devrais pas attendre trop longtemps, va à tes occupations, tu ne voudrais pas finir comme moi."},
            {"Narrateur", "*le vieil homme rigolant pendant que l'enquêteur retourne sur le chemin de la prison*"},
        }
    };

    scenes["ch3"] = {
        "assets/prison.png", "assets/prisonniere_prison.png", "",
        {
            {"Enquêteur", "Enfin devant elle."},
            {"Narrateur", "*malgré l'ambiance pesante*"},
            {"Narrateur", "*l'enquêteur se dit que c'est sa seule chance et prend son courage à deux mains pour débuter la conversation*"},
            {"Enquêteur", "Bonsoir, tu ne me connais pas, mais je suis enquêteur et je viens t'interroger sur l'affaire de meurtre."},
            {"Enquêteur", "Je suis vraiment désolé de venir te déranger, mais ça fait 4 ans que j'enquête."},
            {"Enquêteur", "Et malgré cela, rien. Je n'ai trouvé aucune raison qui pourrait t'avoir poussée à ce crime."},
            {"Enquêteur", "J'en suis même à me demander si tu n'as pas été piégée, si c'est le cas, je peux t'aider."},
            {"Narrateur", "*dit-il d'une voix pleine d'empathie*"},
            {"Enquêteur", "Alors, si tu le veux bien, éclaire ma lanterne, je t'en serais infiniment reconnaissant."},
            {"Enquêteur", "Je t'aiderai à raccourcir ta peine si la raison le permet."},
            {"Narrateur", "*la femme soupire, un soupir qui permet de comprendre que la raison est complexe*"},
            {"Narrateur", "*que ce n'était ni par folie, ni par plaisir*"},
            {"Prisonniere", "Très bien, j'accepte, ai-je vraiment le choix après tout ?"},
            {"Prisonniere", "Si je ne le fais, à cause de ces 14 meurtres, je resterai ici pour le restant de mes jours."},
            {"Prisonniere", "Je vais t'expliquer, en partant du commencement, la raison de mon crime."},
            {"Prisonniere", "Pour toi, que t'inspire le mot 'Maison' ? Qu'est-ce que cela représente, que signifie-t-il pour toi ?"},
            {"Prisonniere", "Certainement ce lieu d'enfance, ce lieu où l'on se sent en sécurité, aimé et protégé."},
            {"Prisonniere", "Cet havre de paix qui, en prenant de l'âge, nous rappelle la meilleure partie de notre vie."},
            {"Prisonniere", "Pour moi, c'est tout l'inverse, le seul mot assez fort pour le décrire est l'ENFER ........."},
        },
        false, true, false
    };

    scenes["ch3_non"] = {
        "assets/prison.png", "assets/prisonniere_prison.png", "",
        {
            {"Prisonniere", "Je voulais t'expliquer, mais tu ne veux plus. Tu es encore plus fou que moi, pars maintenant."},
        },
        true, false, false
    };

    scenes["ch4"] = {
        "assets/entree.png", "assets/prisonniere.png", "ch5",
        {
            {"Narrateur", "*vous vous retrouvez projeté dans les souvenirs de la femme*"},
            {"Narrateur", "*avec elle comme conteuse de sa propre histoire*"},
            {"Prisonniere", "Voici la maison de mon enfance. Mon enfer à portée de main."},
            {"Prisonniere", "Je passais le plus clair de mon temps dehors."},
            {"Prisonniere", "Je rentrais seulement par nécessité et non par choix."},
            {"Prisonniere", "Avec la mort de ma mère, tout a changé."},
            {"Prisonniere", "Les choses sont devenues encore pires."},
            {"Prisonniere", "Pas un jour passé sans que mon père m'attende tous les soirs ici, juste derrière cette porte."},
        }
    };

    scenes["ch5"] = {
        "assets/salon.png", "assets/prisonniere.png", "ch6",
        {
            {"Narrateur", "*vous entrez subitement dans la maison, comme si vous voliez tel un fantôme*"},
            {"Prisonniere", "Et une fois à l'intérieur, mon père, ou Satan comme j'aime aussi l'appeler,"},
            {"Prisonniere", "ne se privait pas de lever la main sur moi jusqu'à être « détendu », comme il disait."},
            {"Prisonniere", "Tous les soirs, la même routine et ce corps qui, peu à peu, criait de douleur."},
            {"Prisonniere", "Mon seul réconfort était cette pièce que je voyais comme mon château fort."},
            {"Prisonniere", "« Le paradis », comme je l'appelais, ma chambre."},
        }
    };

    scenes["ch6"] = {
        "assets/chambre.png", "assets/prisonniere.png", "ch7",
        {
            {"Prisonniere", "À la maison, je m'attardais de plus en plus souvent ici."},
            {"Prisonniere", "Car, mon père ayant vite fait son deuil, il a rapidement retrouvé une femme."},
            {"Prisonniere", "Qui était à son image, si je puis dire, violente, voire même cruelle."},
            {"Prisonniere", "Parfois, la nuit, pendant que j'écoutais de la musique, la seule chose qui me permettait de tenir,"},
            {"Prisonniere", "mon petit réconfort, elle décidait que c'en était trop."},
            {"Prisonniere", "Au lieu de m'avertir que ça l'agacait, elle m'attrapait par le bras, prenait mes habits et me jetait dehors."},
            {"Prisonniere", "Le tout en m'insultant de noms d'une violence indescriptible pour une enfant."},
        }
    };

    scenes["ch7"] = {
        "assets/aube.png", "assets/", "",
        {
            {"Prisonniere", "Un jour, j'en ai eu assez de ces tourments."},
            {"Prisonniere", "Le soir de Noël, avec tous mes bourreaux réunis,"},
            {"Prisonniere", "je pris un couteau dans la cuisine, attendis la tombée de la nuit et, dans leur sommeil,"},
            {"Prisonniere", "les tua sans hésitation, tous ces démons qui hantaient ma vie."},
            {"Prisonniere", "Puis je restais assise dans le salon pendant ce qui me paraissait une éternité, jusqu'à ce que la police arrive."},
            {"Prisonniere", "Alertée par un voisin à cause des cris de douleur."},
            {"Prisonniere", "Et me voilà maintenant, enfermée ici, car j'ai fait le choix de me libérer plutôt que de continuer à subir."},
            {"Prisonniere", "Qu'en penses-tu, toi qui joues : crois-tu que les violences sur lesquelles on ferme les yeux doivent être punies ?"},
            {"Prisonniere", "Penses-tu que, si aucune aide ne vient, il est mieux de se libérer soi-même, au prix de l'enfermement ?"},
            {"Prisonniere", "Il ne faut pas négliger ces violences, encore plus quand cela concerne des enfants."},
        },
		false, false, true
    };

    std::string currentScene = "prologue";

    int  currentLine = 0;

    std::string lastScene = "";

    bool bgLoaded = false;
    bool charLoaded = false;
    bool inMenu = true;

    std::string creditsMessage = "";

    sf::Texture bgTex, charTex;
    sf::Sprite bg(bgTex);
    sf::Sprite character(charTex);

    sf::Text speaker(font, "", 35);

    speaker.setFillColor(sf::Color::Yellow);
    speaker.setPosition({ 120.f, 820.f });

    sf::Text dialogText(font, "", 32);

    dialogText.setFillColor(sf::Color::White);
    dialogText.setPosition({ 120.f, 865.f });

    sf::RectangleShape box({ 1700.f, 220.f });

    box.setPosition({ 110.f, 800.f });
    box.setFillColor(sf::Color(0, 0, 0, 200));
    box.setOutlineColor(sf::Color(255, 255, 255));
    box.setOutlineThickness(3);

    Menu menu(font);
    ChoiceBox choiceBox(font);
    Credits credits(font);

    sf::Clock clock;

    std::string btNextScene = "";

    bool        btShowChoice = false;
    bool        btShowFinalChoice = false;
    bool        btGoCredits = false;

    auto btRoot = std::make_shared<BTSelector>();

    {
        auto seq = std::make_shared<BTSequence>();

        seq->children.push_back(std::make_shared<BTCondition>([&]() 
            {
            return btShowChoice;
            }
            )
        );

        seq->children.push_back(std::make_shared<BTAction>([&]() 
            {
            if (!choiceBox.isVisible()) 
            {
                choiceBox.show(
                    {
                    {"Oui, je t'ecoute.",  "ch4"},
                    {"Non, je n'ai pas le temps.", "ch3_non"}
                    }
                );
            }
            return BTStatus::Success;
            }
            )
        );
        btRoot->children.push_back(seq);
    }

    {
        auto seq = std::make_shared<BTSequence>();

        seq->children.push_back(std::make_shared<BTCondition>([&]() 
            {
            return btShowFinalChoice;
            }
            )
        );
        seq->children.push_back(std::make_shared<BTAction>([&]()
            {
            if (!choiceBox.isVisible()) 
            {
                choiceBox.show
                (
                    {
                    {"Oui, je comprends maintenant.", "credits_liberee"},
                    {"Non, je ne comprends toujours pas.", "credits_prison"}
                    }
                );
            }
            return BTStatus::Success;
            }
            )
        );
        btRoot->children.push_back(seq);
    }

    {
        auto seq = std::make_shared<BTSequence>();

        seq->children.push_back(std::make_shared<BTCondition>([&]() 
            {
            return btGoCredits;
            }
            )
        );
        seq->children.push_back(std::make_shared<BTAction>([&]()
            {
            if (!credits.isVisible())
            {
                credits.show(creditsMessage);
            }
            return BTStatus::Success;
            }
            )
        );
        btRoot->children.push_back(seq);
    }

    while (window.isOpen()) 
    {
        float dt = clock.restart().asSeconds();

        if (inMenu) 
        {
            while (const auto event = window.pollEvent()) 
            {
                if (event->is<sf::Event::Closed>()) window.close();
                const auto* key = event->getIf<sf::Event::KeyPressed>();
                if (key && key->code == sf::Keyboard::Key::Space) 
                {
                    inMenu = false;
                    currentScene = "prologue";
                    currentLine = 0;
                    lastScene = "";
                }
            }
            menu.update(dt);
            menu.draw(window);
            window.display();
            continue;
        }

        if (credits.isVisible()) 
        {
            while (const auto event = window.pollEvent()) 
            {
                if (event->is<sf::Event::Closed>()) window.close();
                const auto* key = event->getIf<sf::Event::KeyPressed>();
                if (key) 
                {
                    bool done = credits.handleKey(key->code);
                    if (done) 
                    {
                        btGoCredits = false;
                        inMenu = true;
                    }
                }
            }
            credits.draw(window);
            window.display();
            continue;
        }

        while (const auto event = window.pollEvent()) 
        {
            if (event->is<sf::Event::Closed>()) window.close();

            const auto* key = event->getIf<sf::Event::KeyPressed>();
            if (!key) continue;

            if (choiceBox.isVisible()) 
            {
                std::string next = "";
                choiceBox.handleKey(key->code, next);
                if (!next.empty()) 
                {
                    btShowChoice = false;
                    btShowFinalChoice = false;
                    if (next == "credits_liberee") 
                    {
                        creditsMessage = "Elle a été libérée peu après. Vous avez fais le bon choix.";
                        btGoCredits = true;
                    }
                    else if (next == "credits_prison") 
                    {
                        creditsMessage = "Elle reste en prison. Certaines maisons devraient rester fermées pour toujours, et certaines mentalitées devraient changer.";
                        btGoCredits = true;
                    }
                    else 
                    {
                        currentScene = next;
                        currentLine = 0;
                        lastScene = "";
                    }
                }
                continue;
            }

            if (key->code == sf::Keyboard::Key::Space) 
            {
                Scene& s = scenes[currentScene];
                if (currentLine < (int)s.dialogues.size() - 1) 
                {
                    currentLine++;
                }
                else 
                {
                    if (s.hasChoice) 
                    {
                        btShowChoice = true;
                    }
                    else if (s.hasFinalChoice) 
                    {
                        btShowFinalChoice = true;
                    }
                    else if (s.isEnd) 
                    {
                        creditsMessage = "Tu n'as pas voulu entendre. Honte à toi; Fin.";
                        btGoCredits = true;
                    }
                    else 
                    {
                        currentScene = s.next;
                        currentLine = 0;
                        lastScene = "";
                    }
                }
            }
        }

        btRoot->tick();

        if (currentScene != lastScene) 
        {
            Scene& s = scenes[currentScene];
            bgLoaded = false;
            charLoaded = false;

            if (!s.bg.empty()) 
            {
                bgLoaded = bgTex.loadFromFile(s.bg);
                if (bgLoaded) 
                {
                    bg.setTexture(bgTex, true);
                    bg.setScale({ 1920.f / (float)bgTex.getSize().x,
                                 1080.f / (float)bgTex.getSize().y });
                    bg.setPosition({ 0.f, 0.f });
                }
                else 
                {
                    std::cerr << "Erreur BG: " << s.bg << "\n";
                }
            }

            if (!s.chara.empty()) 
            {
                charLoaded = charTex.loadFromFile(s.chara);
                if (charLoaded) 
                {
                    character.setTexture(charTex, true);
                    float scale = 650.f / (float)charTex.getSize().y;
                    character.setScale({ scale, scale });
                    float x = 960.f - charTex.getSize().x * scale / 2.f;
                    character.setPosition({ x, 1080.f - 650.f - 220.f });
                }
                else 
                {
                    std::cerr << "Erreur CHAR: " << s.chara << "\n";
                }
            }

            lastScene = currentScene;
        }

        window.clear(sf::Color(20, 20, 30));
        if (bgLoaded)   window.draw(bg);
        window.draw(box);
        if (charLoaded) window.draw(character);

        Scene& s = scenes[currentScene];
        if (!s.dialogues.empty()) 
{
            auto& line = s.dialogues[currentLine];
            speaker.setString(line.first);
            dialogText.setString(line.second);
            window.draw(speaker);
            window.draw(dialogText);
        }

        choiceBox.draw(window);
        window.display();
    }

    return 0;
}