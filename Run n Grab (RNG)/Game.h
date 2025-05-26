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

	Player player;

	Coin* coinTop;
	Coin* coinBottom;	

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

