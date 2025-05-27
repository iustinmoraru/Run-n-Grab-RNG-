#pragma once
#include <iostream>

#include "Player.h"
#include "Meniu.h"
#include "Collectible.h"
#include "Coin.h"
#include "Gem.h"


class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	int nrLives;
	const float distantaInimi = 35.f;

	Player player;

	enum class gameStates {
		MainMenu,
		Playing,
		Lose
	}currentGameState;


	Collectible* collectibleTop;
	Collectible* collectibleBottom;

	sf::Text* txtScore;
	sf::Text* txtLives;
	sf::Font font;
	sf::Texture LivesTexture;
	sf::Sprite* SpriteLives;

	Meniu* mainMenu;

	void initVariables();
	void initWindow();
	void initMainMenu();

public:
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	const bool running() const;
	void pollEvents();

	void update();
	void render();
};

