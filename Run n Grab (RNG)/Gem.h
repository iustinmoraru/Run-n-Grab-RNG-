#pragma once
#include "Collectible.h"
#include <SFML/Graphics.hpp>

class Gem : public Collectible
{
private:
	sf::RectangleShape shape;
	float speed;
	bool colected = false;

public:
    Gem(float x, float y, float radius = 25.f, float speed = 5.f);
    virtual ~Gem();

    void render(sf::RenderTarget* target) override;
    sf::FloatRect getGlobalBounds() const override;
    void onCollect() override;
    void setPosition(float x, float y) override;


    void update(float windowWidth, sf::FloatRect playerBounds, int& nrLives);
    //void render(sf::RenderTarget* target);
    void resetPosition(float x, float y);
    sf::Vector2f getPosition() const;
    float getRadius() const;
    void reset(float x, float y);
    void VerifyColision(sf::FloatRect playerBounds);
};

