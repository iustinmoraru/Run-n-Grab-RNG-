#pragma once
#include <iostream>
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

	void initVariables();
	void initWindow();

public:
	Game();
	~Game();

	//Accessors

	//Modifiers

	//Functions
	void update();
	void render();
};

