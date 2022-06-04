#include "menu.h"

Menu::Menu()
{}

Menu::Menu(float width, float height)
{
	if(!font.loadFromFile("pixelFont.ttf"))
	{
		// handle error
	}
	sf::Text menuElement;
	menuElement.setScale(2, 2);
	menuElement.setFont(font);
	menuElement.setFillColor(sf::Color::Red);
	menuElement.setString("Play");
	menuElement.setPosition(
	  sf::Vector2f((width - menuElement.getLocalBounds().width*menuElement.getScale().x) / 2.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 1));
	menu.push_back(menuElement);

	menuElement.setScale(2, 2);
	menuElement.setFont(font);
	menuElement.setFillColor(sf::Color::Black);
	menuElement.setString("Table  of  scores");
	menuElement.setPosition(
	  sf::Vector2f((width - menuElement.getLocalBounds().width*menuElement.getScale().x) / 2.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 2));
	menu.push_back(menuElement);

	menuElement.setScale(2, 2);
	menuElement.setFont(font);
	menuElement.setFillColor(sf::Color::Black);
	menuElement.setString("Exit");
	menuElement.setPosition(
	  sf::Vector2f((width - menuElement.getLocalBounds().width*menuElement.getScale().x) / 2.0, height / (MAX_NUMBER_OF_ITEMS + 1) * 3));
	menu.push_back(menuElement);

	selectedItemIndex = 0;
}

Menu::~Menu()
{}

void Menu::draw(sf::RenderWindow &window)
{
	font.loadFromFile("pixelFont.ttf");

	window.clear(sf::Color::White);
	for(sf::Text menuElement: menu)
	{
		menuElement.setFont(font);
		window.draw(menuElement);
	}
}

void Menu::MoveUp()
{
	if(selectedItemIndex - 1 >= 0)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex--;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}

void Menu::MoveDown()
{
	if(selectedItemIndex + 1 < MAX_NUMBER_OF_ITEMS)
	{
		menu[selectedItemIndex].setFillColor(sf::Color::Black);
		selectedItemIndex++;
		menu[selectedItemIndex].setFillColor(sf::Color::Red);
	}
}
