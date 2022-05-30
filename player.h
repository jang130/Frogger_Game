#include <SFML/Graphics.hpp>

class Player
{
	private:
	// Position of Player on the screen
	sf::Vector2f mPosition;
	sf::Vector2f mSize;

	// Sprite of Player
	sf::Sprite mSprite;

	// Textures of Player
	sf::Texture mTextureBack;
    sf::Texture mTextureRight;
    sf::Texture mTextureLeft;
	sf::Texture mTextureFront;

	// Which direction(s) is the player currently moving in
	bool mLeftPressed;
	bool mRightPressed;
    bool mUpPressed;
	bool mDownPressed;

	// Player's speed in pixels per second
	float mSpeed;

	double moveWithLog = 0;

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

	unsigned int getHeight() const;
	unsigned int getWidth() const;
	sf::Vector2f getPosition() const;

	void setMoveWithLog(double speed=0);
	double getMoveWithLogSpeed();
	void movePositionWithLog(float elapsedTime);

	// Function that is called once every frame to update display
	void update(float elapsedTime);
	void die(sf::Vector2f newPos);
};