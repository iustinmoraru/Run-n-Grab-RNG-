#include "Gem.h"

Gem::Gem(float x, float y, float radius, float speed)
    : speed(speed)
{
    this->shape.setSize( {radius * 1.41f, radius * 1.41f});
    this->shape.setRotation(sf::degrees(45));
    this->shape.setFillColor(sf::Color::Red);
    this->shape.setPosition({ x, y });
}

Gem::~Gem()
{
}

void Gem::update(float windowWidth, sf::FloatRect playerBounds, int& nrLives)
{
    // Deplasare spre stanga
    this->shape.move(sf::Vector2f(-this->speed, 0.f));

    // Daca a iesit complet din ecran, reseteaza la dreapta
    if (this->shape.getPosition().x + this->shape.getSize().x < 0)
    {
        if (colected == false)
            nrLives--;
        if (colected == true)
            score++;
        colected = false;
        sf::Vector2f currentPos = this->shape.getPosition();
        this->shape.setPosition(sf::Vector2f(windowWidth, currentPos.y));
    }

    VerifyColision(playerBounds);
}


void Gem::render(sf::RenderTarget* target)
{
    if (colected == false)
        target->draw(this->shape);

}

void Gem::resetPosition(float x, float y)
{
    this->shape.setPosition({ x, y });
}

sf::Vector2f Gem::getPosition() const
{
    return this->shape.getPosition();
}

float Gem::getRadius() const
{
    return this->shape.getSize().x;
}


void Gem::reset(float x, float y)
{
    this->shape.setPosition({ x, y });
}

void Gem::VerifyColision(sf::FloatRect playerBounds)
{
    sf::Vector2f topRight = playerBounds.position + sf::Vector2f(playerBounds.size.x, 0);
    sf::Vector2f bottomRight = playerBounds.position + sf::Vector2f(playerBounds.size.x, playerBounds.size.y);
    if (this->shape.getGlobalBounds().contains(topRight))
        colected = true;
    if (this->shape.getGlobalBounds().contains(bottomRight))
        colected = true;
}

sf::FloatRect Gem::getGlobalBounds() const
{
    return this->shape.getGlobalBounds();
}

void Gem::onCollect()
{
    this->colected = true;
}

void Gem::setPosition(float x, float y)
{
    this->shape.setPosition({ x, y });
}
