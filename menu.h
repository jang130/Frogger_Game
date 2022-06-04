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
