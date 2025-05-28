#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;

	try
	{
		if (!font.openFromFile("Assets\\AncizarSans.ttf"))
			throw("Font initializat fara succes");
		txtScore = new sf::Text(font);
		txtScore->setString("Score: ");
		txtScore->setCharacterSize(32);
		txtScore->setPosition({ (window->getSize().x / 2.f) - 80.f , 0.f });
		txtScore->setOutlineColor(sf::Color::Black);
		txtScore->setOutlineThickness(2.f);

		txtLives = new sf::Text(font);
		txtLives->setString("Lives: ");
		txtLives->setCharacterSize(32);
		txtLives->setOutlineColor(sf::Color::Black);
		txtLives->setOutlineThickness(2.f);

		// Lives
		nrLives = 3;
		if (!LivesTexture.loadFromFile("Assets\\heart.png"))
			throw("Eroare la incarcarea texturii pentru inimi");
		SpriteLives = new sf::Sprite(LivesTexture);

		if (!PlayImage.loadFromFile("Assets\\PlayBackground.png"))
			throw("Eroare la incarcarea texturii pentru butonul Play");
		SpritePlayImage = new sf::Sprite(PlayImage);
		SpritePlayImage->setPosition({ 0.f, 0.f });
		SpritePlayImage->setScale({ window->getSize().x / static_cast<float>(SpritePlayImage->getTexture().getSize().x),
			window->getSize().y / static_cast<float>(SpritePlayImage->getTexture().getSize().y) });
	}
	catch (const char* exceptie)
	{
		std::cerr << exceptie << std::endl;
	}
	
}

int Collectible::score = 0;
bool Meniu::SelectedOption = false;

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

	// Initial coin-uri
	this->collectibleTop = new Coin(collectibleTopX, collectibleTopY, coinRadius, 6.f);
	this->collectibleBottom = new Coin(collectibleBottomX, collectibleBottomY, coinRadius, 6.f);
}

void Game::initSelectCollectibleMenu()
{
	SelectableMenu = new Meniu(font, *window);

	SelectableMenu->addOption("Coin", [&]() {
		selectedCollectible = CollectibleType::Coin;
		currentGameState = gameStates::MainMenu;
		ChangeSelectedCollecteble(); 
		});

	SelectableMenu->addOption("Gem", [&]() {
		selectedCollectible = CollectibleType::Gem;
		currentGameState = gameStates::MainMenu;
		ChangeSelectedCollecteble(); 
		});

	SelectableMenu->addOption("Back", [&]() {
		currentGameState = gameStates::MainMenu;
		});
}

void Game::initLoseMenu()
{
	// Clean up the previous menu to avoid memory leaks and dangling pointers
	if (this->loseMenu != nullptr)
	{
		delete this->loseMenu;
		this->loseMenu = nullptr;
	}
	delete this->txtGameOver;
	delete this->txtFinalScore;
	// Init text
	try
	{
		if (!font.openFromFile("Assets\\AncizarSans.ttf"))
			throw("Font initializat fara succes");
		this->txtGameOver = new sf::Text(font);
		this->txtGameOver->setString("Game Over");
		this->txtGameOver->setCharacterSize(45);
		this->txtGameOver->setFillColor(sf::Color(0, 255, 255));
		this->txtGameOver->setOutlineColor(sf::Color::Black);
		this->txtGameOver->setOutlineThickness(5.f);

		this->txtFinalScore = new sf::Text(font);
		this->txtFinalScore->setString("Score " + std::to_string(Collectible::score));
		this->txtFinalScore->setCharacterSize(45);
		this->txtFinalScore->setFillColor(sf::Color(0, 255, 255));
		this->txtFinalScore->setOutlineColor(sf::Color::Black);
		this->txtFinalScore->setOutlineThickness(5.f);

		sf::Vector2u windowSize = this->window->getSize();
		sf::FloatRect gameOverBounds = txtGameOver->getGlobalBounds();
		sf::FloatRect scoreBounds = txtFinalScore->getGlobalBounds();

		txtGameOver->setPosition(sf::Vector2f(windowSize.x / 2.f - gameOverBounds.size.x / 2.f, 100.f));
		txtFinalScore->setPosition(sf::Vector2f(windowSize.x / 2.f - scoreBounds.size.x / 2.f, 180.f));

		this->loseMenu = new Meniu(this->font, *window);
		this->loseMenu->addOption("Play Again", [&]() {
			this->currentGameState = gameStates::Playing;
			nrLives = 3;
			Collectible::score = 0;
			initMainMenu();
			initSelectCollectibleMenu();
			});
		this->loseMenu->addOption("Back to Main Menu", [&]() {
			this->currentGameState = gameStates::MainMenu;
			});
	}
	catch (const char* exceptie)
	{
		std::cerr << exceptie << std::endl;
	}
}

void Game::updateLoseMenu()
{
	this->txtFinalScore->setString("Score " + std::to_string(Collectible::score));
	sf::FloatRect scoreBounds = txtFinalScore->getGlobalBounds();
	txtFinalScore->setPosition(sf::Vector2f(window->getSize().x / 2.f - scoreBounds.size.x / 2.f, 180.f));
}

void Game::initMainMenu()
{
	// Clean up the previous menu to avoid memory leaks and dangling pointers
	if (this->mainMenu != nullptr)
	{
		delete this->mainMenu;
		this->mainMenu = nullptr;
	}

	this->mainMenu = new Meniu(this->font, *window);

	this->mainMenu->addOption("Play", [&]() {
		this->currentGameState = gameStates::Playing;
		// Resetari 
		nrLives = 3;
		Collectible::score = 0;
		});

	this->mainMenu->addOption("Select Collectible", [&]() {
		currentGameState = gameStates::SelectCollectible;
		initSelectCollectibleMenu();
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
	this->initSelectCollectibleMenu();
	this->initLoseMenu();
}

//Destructor
Game::~Game()
{
	delete this->window;
	delete this->collectibleTop;
	delete this->collectibleBottom;
	delete this->txtScore;
	delete this->txtLives;
	delete this->txtGameOver;
	delete this->txtFinalScore;
	delete this->mainMenu;
	delete this->SpriteLives;
	delete this->SelectableMenu;
	delete this->loseMenu;
	delete this->SpritePlayImage;
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

	if (this->currentGameState == gameStates::SelectCollectible && this->SelectableMenu)
	{
		this->SelectableMenu->update(*window);
	}

	if (this->currentGameState == gameStates::Lose && this->loseMenu)
	{
		this->loseMenu->update(*window);
	}

	if (this->currentGameState == gameStates::Playing)
	{
		// Actualizeaza pozitia collectibles
		float windowWidth = this->window->getSize().x;
		this->collectibleTop->update(windowWidth, player.getGlobalBounds(), nrLives);
		this->collectibleBottom->update(windowWidth, player.getGlobalBounds(), nrLives);

		txtScore->setString("Score: " + std::to_string(Collectible::score));

		// Conditia de pierdere
		if (nrLives <= 0)
		{
			try
			{
				fisier.open("Assets\\Score.txt", std::ios::app);
				if (fisier.is_open())
				{
					fisier << *this << std::endl;
					fisier.close();
				}
				else
					throw("Eroare la deschiderea fisierului");
			}
			catch (const char* exceptie)
			{
				std::cerr << exceptie << std::endl;
			}

			updateLoseMenu();
			this->currentGameState = gameStates::Lose;
		}
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		Meniu::SelectedOption = true;
	else
		Meniu::SelectedOption = false;
}

void Game::render()
{
    this->window->clear();

	try
	{
		if (this->currentGameState != gameStates::MainMenu && this->currentGameState != gameStates::SelectCollectible && this->currentGameState != gameStates::Lose
			&& this->currentGameState != gameStates::Playing)
			throw("Starea jocului nedifinita");
		if (this->currentGameState == gameStates::MainMenu)
		{
			this->mainMenu->draw(*window);
		}

		if (this->currentGameState == gameStates::SelectCollectible)
		{
			this->SelectableMenu->draw(*window);
		}

		if (this->currentGameState == gameStates::Lose)
		{
			this->loseMenu->draw(*window);
			this->window->draw(*txtGameOver);
			this->window->draw(*txtFinalScore);
		}

		if (this->currentGameState == gameStates::Playing)
		{
			this->window->draw(*SpritePlayImage);

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
	}
	catch (const char* exceptie)
	{
		std::cerr << exceptie << std::endl;
	}

	this->window->display();
}

void Game::ChangeSelectedCollecteble()
{
	if (collectibleTop && collectibleBottom) {
		delete collectibleTop;
		delete collectibleBottom;
	}
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

	// Initializare collectebles
	if (selectedCollectible == CollectibleType::Coin) {
		this->collectibleTop = new Coin(collectibleTopX, collectibleTopY, coinRadius, 6.f);
		this->collectibleBottom = new Coin(collectibleBottomX, collectibleBottomY, coinRadius, 6.f);
	}
	else {
		this->collectibleTop = new Gem(collectibleTopX, collectibleTopY, coinRadius, 6.f);
		this->collectibleBottom = new Gem(collectibleBottomX, collectibleBottomY, coinRadius, 6.f);
	}
}

std::ostream& operator<<(std::ostream& c, Game& g)
{
	std::string coin = "Coin ";
	std::string gem = "Gem ";
	if (g.selectedCollectible == Game::CollectibleType::Coin)
		c << coin;
	if (g.selectedCollectible == Game::CollectibleType::Gem)
		c << gem;
	c << Collectible::score;
	return c;
}
