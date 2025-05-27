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

int Coin::score = 0;

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
	const float coinTopY = 225.f;
	const float cointBottomY = 545.f;

	// Distanta orizontala dorita intre coin-uri
	const float coinHorizontalDistance = 350.f;

	// Pozitii orizontale initiale
	const float coinTopX = windowWidth;
	const float coinBottomX = windowWidth + coinHorizontalDistance;

	// Initializare coin-uri
	this->coinTop = new Coin(coinTopX, coinTopY, coinRadius, 6.f); // sus
	this->coinBottom = new Coin(coinBottomX, cointBottomY, coinRadius, 6.f); // jos
}

//Constructor
Game::Game()
{
	this->initWindow();
	this->initVariables();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->coinTop;
	delete this->coinBottom;
	delete this->txtScore;
	delete this->txtLives;
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

	//std::cout << Coin::score << std::endl;

	// Actualizeaza pozitia monedelor
	float windowWidth = this->window->getSize().x;
	this->coinTop->update(windowWidth, player.getGlobalBounds());
	this->coinBottom->update(windowWidth, player.getGlobalBounds());

	txtScore->setString("Score: " + std::to_string(Coin::score));
}

void Game::render()
{
    this->window->clear();

	//Render game objects here
	this->player.render(this->window);

	this->coinTop->render(this->window);
	this->coinBottom->render(this->window);

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

	this->window->display();
}
