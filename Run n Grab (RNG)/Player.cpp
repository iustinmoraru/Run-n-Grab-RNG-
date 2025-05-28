#include "Player.h"

void Player::initVariables()
{
	this->movementSpeed = 10.f;
	this->gravity = 0.5f;
	this->velocityY = 0.f;
	this->jumpStrength = -18.f;
	this->isOnGround = false;
}

void Player::initShape()
{
	this->shape.setFillColor(sf::Color::Cyan);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
}

Player::Player(float x, float y)
{
	this->currentAnimation = AnimationStates::IDLE;
	this->shape.setPosition({ x, y });

	this->initVariables();
	this->initShape();

	try
	{
		if (this->playerTexture.loadFromFile("Assets/Player/Idle.png"))
		{
			std::cout << "Player Image loaded" << std::endl;
			this->playerSprite = new sf::Sprite(playerTexture);
			this->playerSprite->setTextureRect(sf::IntRect({ this->frameIndex * 128, 0 }, { 128, 128 }));
		}
		else
		{
			std::string mesaj = "Eroare la incarcarea imaginii platyerului";
			throw(mesaj);
		}
	}
	catch (std::string msg)
	{
		std::cerr << msg << std::endl;
	}
	loadAnimations();
	setPlayerAnimation(AnimationStates::RUNNING);
}

Player::~Player()
{
	delete this->playerSprite;
}

void Player::updateInput()
{
	//Keyboard input
	//Left
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	//{
	//	this->shape.move({ -this->movementSpeed, 0.f });
	//	
	//}
	////Right
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	//{
	//	this->shape.move({ this->movementSpeed, 0.f });

	//}
	////Up
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W))
	//{
	//	this->shape.move({ 0.f, -this->movementSpeed });

	//}
	////Down
	//else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
	//{
	//	this->shape.move({ 0.f, this->movementSpeed });

	//}
	// Sari doar daca esti pe sol
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W) && this->isOnGround)
	{
		this->velocityY = this->jumpStrength;
		this->isOnGround = false;
	}
	if (this->isOnGround == false)
		this->setPlayerAnimation(AnimationStates::JUMPING);
	else
		this->setPlayerAnimation(AnimationStates::RUNNING);
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();

	sf::Vector2f position = this->shape.getPosition();

	// Left
	if (playerBounds.position.x <= 0.f)
		position.x = 0.f;

	// Right
	if (playerBounds.position.x + playerBounds.size.x >= target->getSize().x)
		position.x = target->getSize().x - playerBounds.size.x;

	// Top
	if (playerBounds.position.y <= 0.f)
		position.y = 0.f;

	// Bottom
	if (playerBounds.position.y + playerBounds.size.y >= target->getSize().y)
		position.y = target->getSize().y - playerBounds.size.y;

	this->shape.setPosition(position);
}


void Player::update(const sf::RenderTarget* target, float dt)
{
	this->updateInput();

	// Aplica gravitatia
	this->velocityY += this->gravity;
	this->shape.move(sf::Vector2f(0.f, this->velocityY));

	playerSprite->setPosition(this->shape.getPosition() + offset);

	// Coliziune cu solul (partea de jos a ferestrei)
	sf::FloatRect playerBounds = this->shape.getGlobalBounds();
	float windowHeight = static_cast<float>(target->getSize().y);

	if (playerBounds.position.y + playerBounds.size.y >= windowHeight)
	{
		sf::Vector2f currentPosition = this->shape.getPosition();
		this->shape.setPosition(sf::Vector2f(currentPosition.x, windowHeight - playerBounds.size.y));
		this->velocityY = 0.f;
		this->isOnGround = true;
	}
	else
	{
		this->isOnGround = false;
	}

	//Actualizare animatie
	this->animationTimer += dt;
	if (animationTimer > Animations[currentAnimation].animationSpeed)
	{
		this->playerSprite->setTextureRect(sf::IntRect({ this->frameIndex * 128, 0 }, { 128, 128 }));
		this->frameIndex = (this->frameIndex + 1) % this->numberOfFrames;
		this->animationTimer = 0.f;
	}

}


void Player::render(sf::RenderTarget* target)
{
	//target->draw(this->shape);
	target->draw(*this->playerSprite);
}

sf::FloatRect Player::getGlobalBounds()
{
	return shape.getGlobalBounds();
}

void Player::setPosition(float x, float y)
{
	this->shape.setPosition({ x, y });
}

void Player::setPlayerAnimation(AnimationStates state)
{
	if (this->currentAnimation != state)
	{
		this->currentAnimation = state;
		this->playerSprite->setTextureRect(this->Animations[state].frames[0]);
		this->playerSprite->setTexture(this->Animations[state].texture);
		this->frameIndex = 0;
		this->animationTimer = 0.f;
		this->numberOfFrames = this->Animations[state].frames.size();
	}
	else
	{
		this->playerSprite->setTextureRect(this->Animations[state].frames[this->frameIndex]);
	}
}

void Player::loadAnimations()
{
	try
	{
		// Load RUNNING animation
		Animation running;
		if (running.texture.loadFromFile("Assets/Player/Run.png"))
		{
			running.animationSpeed = 0.06f; // Adjust speed as needed
			running.frames.push_back(sf::IntRect({ 0, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 1 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 2 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 3 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 4 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 5 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 6 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 7 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 8 * 128, 0 }, { 128, 128 }));
			running.frames.push_back(sf::IntRect({ 9 * 128, 0 }, { 128, 128 }));
			this->Animations[AnimationStates::RUNNING] = running;
		}
		// Load JUMPING animation
		Animation jumping;
		if (jumping.texture.loadFromFile("Assets/Player/Run.png"))
		{
			jumping.animationSpeed = 5.f; // Adjust speed as needed
			jumping.frames.push_back(sf::IntRect({ 7 * 128, 0 }, { 128, 128 }));
			this->Animations[AnimationStates::JUMPING] = jumping;
		}
	}
	catch (const std::exception& e)
	{
		std::cerr << "Error loading animations: " << e.what() << std::endl;
	}
}

std::ostream& operator<<(std::ostream& c, Player& p)
{
	c << p.shape.getPosition().x << " " << p.shape.getPosition().y << std::endl;
	return c;
}
