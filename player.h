#include <SFML/Graphics.hpp>

class Player
{
	private:
	// Position of Player on the screen
	sf::Vector2f mPosition;

	// Sprite of Player
	sf::Sprite mSprite;

	// Textures of Player
	sf::Texture mTexture;
    sf::Texture mTextureRight;
    sf::Texture mTextureLeft;

	// Which direction(s) is the player currently moving in
	bool mLeftPressed;
	bool mRightPressed;
    bool mUpPressed;
	bool mDownPressed;

	// Player's speed in pixels per second
	float mSpeed;

	public:
	// Constructor
	Player();

	//Set Player position
	void setPosition(sf::Vector2f &pos);

	// Send a copy of the sprite to main
	sf::Sprite getSprite();

	// Move Player in a specific direction
	void moveLeft();
	void moveRight();
    void moveUp();
	void moveDown();

	// Stop Player moving in a specific direction
	void stopLeft();
	void stopRight();
    void stopUp();
	void stopDown();

	// Function that is called once every frame to update display
	void update(float elapsedTime);
};