#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;

}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode({ 800, 600 });
	this->window = new sf::RenderWindow(this->videoMode, "Run n Grab", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	// Initializare coin-uri dupa crearea ferestrei
	float coinRadius = 25.f;
	float windowWidth = this->window->getSize().x;
	float windowHeight = this->window->getSize().y;

	// Pozitii verticale
	float coinTopY = 225.f;
	float cointBottomY = 545.f;

	// Distanta orizontala dorita intre coin-uri
	float coinHorizontalDistance = 300.f;

	// Pozitii orizontale initiale
	float coinTopX = windowWidth;
	float coinBottomX = windowWidth + coinHorizontalDistance;

	// Initializare coin-uri
	this->coinTop = new Coin(coinTopX, coinTopY, coinRadius, 6.f); // sus
	this->coinBottom = new Coin(coinBottomX, cointBottomY, coinRadius, 6.f); // jos
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

const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()
{
    while (const std::optional event = window->pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window->close();
        }
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                window->close();
        }
    }
}

void Game::update()
{
	this->pollEvents();

	this->player.update(this->window);

	std::cout << player;

	// Actualizeaza pozitia monedelor
	float windowWidth = this->window->getSize().x;
	this->coinTop->update(windowWidth);
	this->coinBottom->update(windowWidth);
}

void Game::render()
{
    this->window->clear();

	//Render game objects here
	this->player.render(this->window);

	this->coinTop->render(this->window);
	this->coinBottom->render(this->window);

	this->window->display();
}
