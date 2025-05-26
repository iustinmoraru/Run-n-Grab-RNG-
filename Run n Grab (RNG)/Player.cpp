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
	this->shape.setFillColor(sf::Color::Blue);
	this->shape.setSize(sf::Vector2f(50.f, 50.f));

}

Player::Player(float x, float y)
{
	this->shape.setPosition({ x, y });

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

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


void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	// Aplica gravitatia
	this->velocityY += this->gravity;
	this->shape.move(sf::Vector2f(0.f, this->velocityY));

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

	// (Optional) Coliziune cu marginile ferestrei (sus, stanga, dreapta)
	// this->updateWindowBoundsCollision(target);
}


void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

std::ostream& operator<<(std::ostream& c, Player& p)
{
	c << p.shape.getPosition().x << " " << p.shape.getPosition().y << std::endl;
	return c;
}
