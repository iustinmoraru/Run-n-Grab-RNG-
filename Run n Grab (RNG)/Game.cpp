#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;

	if (!font.openFromFile("Assets\\AncizarSans.ttf"))
		std::cout << "Font initializat fara succes" << std::endl;
	txtScore = new sf::Text(font);
	txtScore->setString("Score: ");
	txtScore->setCharacterSize(32);
	txtScore->setPosition({ (window->getSize().x / 2.f) - 80.f , 0.f });

	txtLives = new sf::Text(font);
	txtLives->setString("Lives: ");
	txtLives->setCharacterSize(32);

	// Lives
	nrLives = 3;
	if (!LivesTexture.loadFromFile("Assets\\heart.png"))
		std::cout << "Textura neinitializata";
	SpriteLives = new sf::Sprite(LivesTexture);
	
}

int Collectible::score = 0;

void Game::initWindow()
{
	this->videoMode = sf::VideoMode({ 800, 600 });
	this->window = new sf::RenderWindow(this->videoMode, "Run n Grab", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);

	// Setam pozitia player
	this->player.setPosition(0.f, window->getSize().x - player.getGlobalBounds().size.y);

	// Initializare coin-uri dupa crearea ferestrei
	float coinRadius = 25.f;
	float windowWidth = this->window->getSize().x;
	float windowHeight = this->window->getSize().y;

	// Pozitii verticale
	const float collectibleTopY = 225.f;
	const float collectibleBottomY = 545.f;

	// Distanta orizontala dorita intre coin-uri
	const float collectibleHorizontalDistance = 350.f;

	// Pozitii orizontale initiale
	const float collectibleTopX = windowWidth;
	const float collectibleBottomX = windowWidth + collectibleHorizontalDistance;

	// Initializare coin-uri
	this->collectibleTop = new Gem(collectibleTopX, collectibleTopY, coinRadius, 6.f); // sus
	this->collectibleBottom = new Gem(collectibleBottomX, collectibleBottomY, coinRadius, 6.f); // jos
}

void Game::initMainMenu()
{
	this->mainMenu = new Meniu(this->font);

	this->mainMenu->addOption("Play", [&]() {
		this->currentGameState = gameStates::Playing;
		});

	this->mainMenu->addOption("Select Collectible", [&]() {
		this->window->close();
		});

	this->mainMenu->addOption("Exit", [&]() {
		this->window->close();
		});

}

//Constructor
Game::Game()
{
	this->initWindow();
	this->initVariables();
	this->initMainMenu();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->collectibleTop;
	delete this->collectibleBottom;
	delete this->txtScore;
	delete this->txtLives;
	delete this->mainMenu;
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

	if (this->currentGameState == gameStates::MainMenu)
	{
		this->mainMenu->update(*window);
	}



	//std::cout << Coin::score << std::endl;

	if (this->currentGameState == gameStates::Playing)
	{
		// Actualizeaza pozitia monedelor
		float windowWidth = this->window->getSize().x;
		this->collectibleTop->update(windowWidth, player.getGlobalBounds(), nrLives);
		this->collectibleBottom->update(windowWidth, player.getGlobalBounds(), nrLives);

		txtScore->setString("Score: " + std::to_string(Collectible::score));

		// Conditia de pierdere
		if (nrLives <= 0)
		{
			std::cout << "Ai pierdut!" << std::endl;
			this->window->close();
		}
	}
}

void Game::render()
{
    this->window->clear();

	if (this->currentGameState == gameStates::MainMenu)
	{
		this->mainMenu->draw(*window);
	}
	
	if (this->currentGameState == gameStates::Playing)
	{
		// Render game objects here
		this->player.render(this->window);

		this->collectibleTop->render(this->window);
		this->collectibleBottom->render(this->window);

		this->window->draw(*txtScore);
		this->window->draw(*txtLives);

		// Pozitia de start pentru prima inima dupa text-ul Lives
		sf::FloatRect livesBounds = txtLives->getGlobalBounds();
		float startX = livesBounds.position.x + livesBounds.size.x + 10.f;
		float y = txtLives->getPosition().y;

		for (int i = 0; i < nrLives; i++)
		{
			SpriteLives->setPosition({ startX + i * distantaInimi, y + 10.f });
			this->window->draw(*SpriteLives);
		}
	}

	this->window->display();
}
