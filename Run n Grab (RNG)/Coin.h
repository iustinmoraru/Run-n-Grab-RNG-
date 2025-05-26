#pragma once
#include <SFML/Graphics.hpp>

class Coin
{
private:
    sf::CircleShape shape;
    float speed;

public:
    Coin(float x, float y, float radius = 25.f, float speed = 5.f);
    virtual ~Coin();

    void update(float windowWidth);
    void render(sf::RenderTarget* target);

    void resetPosition(float x, float y);

    sf::Vector2f getPosition() const;
    float getRadius() const;
};
