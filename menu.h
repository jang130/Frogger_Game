/**
 * @file menu.h
 *
 * @brief class for handling menu contrlling
 * @authors Kamil Kośnik, Adam Moszczyński
 * @contact: kamilkosnik@gmail.com, adm.moszczynski@gmail.com
 *
 */

#ifndef MENU_H
#define MENU_H

#include "SFML/Graphics.hpp"
#include <memory>

#define MAX_NUMBER_OF_ITEMS 3

class Menu
{
	private:
	int selectedItemIndex;
	sf::Font font;
	std::vector<sf::Text> menu;

	public:
	Menu();
	Menu(float width, float height);
	~Menu();

	void draw(sf::RenderWindow &window);
	void MoveUp();
	void MoveDown();
	int GetPressedItem()
	{
		return selectedItemIndex;
	}
};

#endif
