#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode({ 800, 600 }); 
	this->window = new sf::RenderWindow(this->videoMode, "Run n Grab", sf::Style::Titlebar | sf::Style::Close);
}

//Constructor
Game::Game()
{
	this->initVariables();
	this->initWindow();
}


//Destructor
Game::~Game()
{
	delete this->window;
}

void Game::update()
{
}

void Game::render()
{
}
