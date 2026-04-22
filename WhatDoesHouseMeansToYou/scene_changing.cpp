#include "scene_changing.h"

scene_changing::scene_changing() : nextSceneId("prologue1"), chapter(0), transitionDuration(1.0f), waitForClick(true)
{}

void scene_changing::changeScene(const std::string& sceneId, sf::Texture& backgroundTexture, sf::Sprite& backgroundSprite, sf::Music& music, sf::Text& dialogue)
{
	nextSceneId = sceneId;

	if (sceneId == "prologue1")
	{
		backgroundTexture.loadFromFile("assets/bureauS.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/prologue_music.ogg");
		music.play();

		dialogue.setString("This is the prologue. Welcome to the story.");

		nextSceneId = "chapter1";
	}

	else if (sceneId == "chapter1")
	{
		backgroundTexture.loadFromFile("assets/ville.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/chapter1_music.ogg");
		music.play();

		dialogue.setString("This is the first scene of chapter 1.");

		nextSceneId = "chapter2";
	}

	else if (sceneId == "chapter2")
	{
		backgroundTexture.loadFromFile("assets/metro.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/chapter2_music.ogg");
		music.play();

		dialogue.setString("This is the first scene of chapter 2.");

		nextSceneId = "chapter3";
	}

	else if (sceneId == "chapter3")
	{
		backgroundTexture.loadFromFile("assets/prison.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/chapter3_music.ogg");
		music.play();

		dialogue.setString("This is the first scene of chapter 3.");

		nextSceneId = "chapter4";
	}
	
	else if (sceneId == "chapter4")
	{
		backgroundTexture.loadFromFile("assets/prison.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/chapter3_music.ogg");
		music.play();

		dialogue.setString("This is the first scene of chapter 4.");

		nextSceneId = "chapter5";
	}

	else if (sceneId == "chapter5")
	{
		backgroundTexture.loadFromFile("assets/prison.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/chapter3_music.ogg");
		music.play();

		dialogue.setString("This is the first scene of chapter 5.");

		nextSceneId = "chapter6";
	}

	else if (sceneId == "chapter6")
	{
		backgroundTexture.loadFromFile("assets/prison.png");
		backgroundSprite.setTexture(backgroundTexture);

		music.stop();
		music.openFromFile("assets/chapter3_music.ogg");
		music.play();

		dialogue.setString("This is the first scene of chapter 5.");

		nextSceneId = "ending";
	}

	else if (sceneId == "ending")
	{
		backgroundTexture.loadFromFile("assets/ending.png");
		backgroundSprite.setTexture(backgroundTexture);
		music.stop();
		music.openFromFile("assets/ending_music.ogg");
		music.play();
		dialogue.setString("This is the ending of the story.");

		nextSceneId = "credits";
	}
	else if (sceneId == "credits")
	{
		backgroundTexture.loadFromFile("assets/credits.png");
		backgroundSprite.setTexture(backgroundTexture);
		music.stop();
		music.openFromFile("assets/credits_music.ogg");
		music.play();
		dialogue.setString("Credits:\n\nDeveloper: Your Name\nArtist: Artist Name\nMusic: Musician Name");
	}
	else
	{
		dialogue.setString("Scene not found.");
	}
}