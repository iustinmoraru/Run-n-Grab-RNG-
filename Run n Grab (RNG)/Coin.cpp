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

void Coin::update(float windowWidth)
{
    // Deplasare spre stanga
    this->shape.move(sf::Vector2f(-this->speed, 0.f));

    // Daca a iesit complet din ecran, reseteaza la dreapta
    if (this->shape.getPosition().x + this->shape.getRadius() * 2 < 0)
    {
        sf::Vector2f currentPos = this->shape.getPosition();
        this->shape.setPosition(sf::Vector2f(windowWidth, currentPos.y));
    }
}


void Coin::render(sf::RenderTarget* target)
{
    target->draw(this->shape);
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
