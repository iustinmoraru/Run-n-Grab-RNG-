#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

class Meniu
{
	sf::Font font;

	struct MenuOption
	{
		std::string txtBox;
		std::function<void()> action;
	};
	std::vector<MenuOption> options;
	std::vector<sf::Text> txtOptions;

public:
	static bool SelectedOption;

	Meniu(sf::Font& font);
	~Meniu();

	bool isHovered(sf::FloatRect optionBounds, sf::RenderWindow& window, size_t i);
	void handleInputs(sf::RenderWindow& window);

	void addOption(std::string text, std::function<void()> action);

	void update(sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);
};

