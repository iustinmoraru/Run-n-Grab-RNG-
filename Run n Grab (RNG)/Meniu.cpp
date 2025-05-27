#include "Meniu.h"

Meniu::Meniu(sf::Font& font) : font(font)
{

}

Meniu::~Meniu()
{

}
bool Meniu::isHovered(sf::FloatRect optionBounds, sf::RenderWindow& window, size_t i)
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	sf::Vector2f mousePosF(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
	return optionBounds.contains(mousePosF);
}

void Meniu::handleInputs(sf::RenderWindow& window)
{
	for (rsize_t i = 0; i < txtOptions.size(); ++i)
	{
		sf::FloatRect optionBounds = txtOptions[i].getGlobalBounds();
		if (isHovered(optionBounds, window, i) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && SelectedOption == false)
		{
			options[i].action();
			break;
		}
	}
}

void Meniu::addOption(std::string text, std::function<void()> action)
{
	MenuOption newOption;
	newOption.txtBox = text;
	newOption.action = action;
	options.push_back(newOption);
}

void Meniu::update(sf::RenderWindow& window)
{
	txtOptions.clear();
	for (size_t i = 0; i < options.size(); ++i)
	{
		sf::Text optionText(font);
		optionText.setString(options[i].txtBox);
		optionText.setCharacterSize(50);
		//optionText.setOrigin({ 0.f, 0.f });
		optionText.scale({ 0.5f, 0.5f });
		optionText.setPosition({ 50.f, 50.f + i * 36.f });
		sf::FloatRect optionBounds = optionText.getGlobalBounds();
		optionText.setFillColor(isHovered(optionBounds, window, i) ? sf::Color::Yellow : sf::Color::White);
		txtOptions.push_back(optionText);
	}
	this->handleInputs(window);
}

void Meniu::draw(sf::RenderWindow& window)
{
	for (const auto& textOption : txtOptions)
	{
		window.draw(textOption);
	}
}
