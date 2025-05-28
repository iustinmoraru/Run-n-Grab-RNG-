#include "Meniu.h"

Meniu::Meniu(sf::Font& font, sf::RenderWindow& window) : font(font)
{
	initializareBackground(window);
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
		optionText.setFillColor(isHovered(optionBounds, window, i) ? sf::Color::Yellow : sf::Color(0, 255, 255));
		optionText.setOutlineColor(sf::Color::Black);
		optionText.setOutlineThickness(8.f);
		txtOptions.push_back(optionText);
	}
	this->handleInputs(window);
}

void Meniu::draw(sf::RenderWindow& window)
{
	window.draw(*SpriteMeniu);
	for (const auto& textOption : txtOptions)
	{
		window.draw(textOption);
	}
}

void Meniu::initializareBackground(sf::RenderWindow& window)
{
	try
	{
		if (!MeniuImage.loadFromFile("Assets\\MeniuBackground.JPG"))
			throw("Eroare la incarcarea texturii pentru inimi");
		SpriteMeniu = new sf::Sprite(MeniuImage);
		SpriteMeniu->setPosition({ 0.f, 0.f });
		SpriteMeniu->setScale({ window.getSize().x / static_cast<float>(SpriteMeniu->getTexture().getSize().x),
			window.getSize().y / static_cast<float>(SpriteMeniu->getTexture().getSize().y) });
	}
	catch (const char* exceptie)
	{
		std::cerr << exceptie << std::endl;
	}
}

