#pragma once
#include <iostream>

#include "Coin.h"
#include "Player.h"


class Game
{
private:
	sf::VideoMode videoMode;
	sf::RenderWindow* window;
	bool endGame;
	int nrLives;
	const float distantaInimi = 35.f;

	Player player;

	Coin* coinTop;
	Coin* coinBottom;
	sf::Text* txtScore;
	sf::Text* txtLives;
	sf::Font font;
	sf::Texture LivesTexture;
	sf::Sprite* SpriteLives;

	void initVariables();
	void initWindow();

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

