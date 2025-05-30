#pragma once
#include <iostream>
#include <fstream>
#include "Player.h"
#include "Meniu.h"
#include "Collectible.h"
#include "Coin.h"
#include "Gem.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	int nrLives;
	const float distantaInimi = 35.f;
	std::ofstream fisier;
	int highScore = 0; 

	Player player;

	enum class gameStates {
		MainMenu,
		Playing,
		SelectCollectible,
		Lose
	}currentGameState;

	enum class CollectibleType { Coin, Gem };
	CollectibleType selectedCollectible;

	Collectible* collectibleTop;
	Collectible* collectibleBottom;

	sf::Text* txtScore;
	sf::Text* txtLives;
	sf::Text* txtGameOver;
	sf::Text* txtFinalScore;
	sf::Text* txtHighScore;
	sf::Font font;
	sf::Texture LivesTexture;
	sf::Sprite* SpriteLives;
	sf::Texture PlayImage;
	sf::Sprite* SpritePlayImage;

	Meniu* mainMenu;
	Meniu* SelectableMenu;
	Meniu* loseMenu;

	void initVariables();
	void initWindow();

	void initMainMenu();
	void initSelectCollectibleMenu();
	void initLoseMenu();
	void updateLoseMenu();

public:
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void update(float dt);
	void render();

	void ChangeSelectedCollecteble();
	void getHighScore();
	void handleInputs();

	friend std::ostream& operator<< (std::ostream& c, Game& g);
	friend std::istream& operator>> (std::istream& c, Game& g);
};

