#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Collectible
{
public:
	static int score;
	virtual ~Collectible() = default;

	// Deseneaza obiectul pe ecran
	virtual void render(sf::RenderTarget* target) = 0;

	virtual sf::FloatRect getGlobalBounds() const = 0;

	virtual void onCollect() = 0;

	// Pozitioneaza obiectul
	virtual void setPosition(float x, float y) = 0;

	virtual void update(float windowWidth, sf::FloatRect playerBounds, int& nrLives) = 0;
};

