#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <string>

#pragma once
class scene_changing
{
private:
	std::string nextSceneId;

	int chapter;

	float transitionDuration;

	bool waitForClick;

public:
	enum class chapters
		{
		prologue,
		chapter1,
		chapter2,
		chapter3,
		chapter4,
		chapter5,
		chapter6
	};

	enum class transitions
	{
		fadeIn,
		fadeOut,
		slideLeft,
		slideRight,
	};

public:
	scene_changing();
	~scene_changing() = default;

	void changeScene(const std::string& sceneId, sf::Texture& backgroundTexture, sf::Sprite& backgroundSprite, sf::Music& music, sf::Text& dialogue);

private:
	transitions currentTransition = transitions::fadeIn;

	//pour la méthode de fade je dois faire par rapport à la transparence que soit elle part de 0 puis vers vers 1 pour fade in et fade out inverse je fait :
	// transparence = transparence_min - (transparence_max - transparence_min) * delta_time;
	//pour le slide pareil interpolation linéaire mais au lieu de transparance une pour le x et une pour le y :
};