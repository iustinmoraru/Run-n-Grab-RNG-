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
	bool stateChangeRequested = false;

	Player player;

	enum class gameStates {
		MainMenu,
		Playing,
		SelectCollectible,
		nextGameState,
		Lose
	}currentGameState;

	enum class CollectibleType { Coin, Gem };
	CollectibleType selectedCollectible = CollectibleType::Coin;


	Collectible* collectibleTop;
	Collectible* collectibleBottom;

	sf::Text* txtScore;
	sf::Text* txtLives;
	sf::Font font;
	sf::Texture LivesTexture;
	sf::Sprite* SpriteLives;

	Meniu* mainMenu;
	Meniu* SelectableMenu;

	void initVariables();
	void initWindow();
	void initMainMenu();

	void initSelectCollectibleMenu();

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

