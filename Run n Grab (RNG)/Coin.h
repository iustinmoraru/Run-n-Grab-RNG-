#pragma once
#include <SFML/Graphics.hpp>

class Coin
{
private:
    sf::CircleShape shape;
    float speed;
    bool colected = false;

public:
    static int score;
    Coin(float x, float y, float radius = 25.f, float speed = 5.f);
    virtual ~Coin();

    void update(float windowWidth, sf::FloatRect playerBounds);
    void render(sf::RenderTarget* target);

    void resetPosition(float x, float y);

    sf::Vector2f getPosition() const;
    float getRadius() const;

    void reset(float x, float y);

    void VerifyColision(sf::FloatRect playerBounds);
};
