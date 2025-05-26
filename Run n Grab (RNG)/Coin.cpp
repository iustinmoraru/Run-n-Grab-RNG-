#include "Coin.h"

Coin::Coin(float x, float y, float radius, float speed)
    : speed(speed)
{
    this->shape.setRadius(radius);
    this->shape.setFillColor(sf::Color::Yellow);
    this->shape.setPosition({ x, y });
}


Coin::~Coin()
{
}

void Coin::update(float windowWidth, sf::FloatRect playerBounds)
{
    // Deplasare spre stanga
    this->shape.move(sf::Vector2f(-this->speed, 0.f));

    // Daca a iesit complet din ecran, reseteaza la dreapta
    if (this->shape.getPosition().x + this->shape.getRadius() * 2 < 0)
    {
        if (colected == true)
            score++;
        colected = false;
        sf::Vector2f currentPos = this->shape.getPosition();
        this->shape.setPosition(sf::Vector2f(windowWidth, currentPos.y));
    }

    VerifyColision(playerBounds);
}


void Coin::render(sf::RenderTarget* target)
{
    if (colected == false)
    {
        target->draw(this->shape);
    }
}

void Coin::resetPosition(float x, float y)
{
    this->shape.setPosition({ x, y });
}

sf::Vector2f Coin::getPosition() const
{
    return this->shape.getPosition();
}

float Coin::getRadius() const
{
    return this->shape.getRadius();
}


void Coin::reset(float x, float y)
{
    this->shape.setPosition({ x, y });
}

void Coin::VerifyColision(sf::FloatRect playerBounds)
{
    sf::Vector2f topRight = playerBounds.position + sf::Vector2f(playerBounds.size.x, 0);
    sf::Vector2f bottomRight = playerBounds.position + sf::Vector2f(playerBounds.size.x, playerBounds.size.y);
    if (this->shape.getGlobalBounds().contains(topRight))
        colected = true;
    if (this->shape.getGlobalBounds().contains(bottomRight))
        colected = true;
}
