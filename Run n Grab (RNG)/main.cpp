#include "Game.h"


int main() {
	

	//Initialize game object
	Game game;
	sf::Clock clock;
	float dt = 0.f;
	//Game loop
	while (game.running())
	{
		dt = clock.getElapsedTime().asSeconds();
		clock.reset();
		clock.start();

		game.update(dt);
		game.render();
	}

	//End of application
	return 0;
}