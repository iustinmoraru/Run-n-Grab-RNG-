#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Player
{
private:
	enum class AnimationStates
	{
		IDLE,
		RUNNING,
		JUMPING
	} currentAnimation;
	struct Animation
	{
		sf::Texture texture;
		std::vector<sf::IntRect> frames;
		float animationSpeed = 0.f; 
	};

	sf::Texture playerTexture;
	sf::Sprite* playerSprite;

	sf::RectangleShape shape;

	float movementSpeed;
	int frameIndex;
	float animationTimer;
	const sf::Vector2f offset = { -32.f, -78.f }; // Offset for sprite animation

	std::unordered_map<AnimationStates, Animation> Animations; // Dictionar
	int numberOfFrames;

	float gravity;
	float velocityY;
	float jumpStrength;
	bool isOnGround;

	void initVariables();
	void initShape();


public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target, float dt);
	void render(sf::RenderTarget* target);
	sf::FloatRect getGlobalBounds();
	void setPosition(float x, float y);
	void setPlayerAnimation(AnimationStates state);
	void loadAnimations();

	friend std::ostream& operator << (std::ostream &c, Player &p);
};

