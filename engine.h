#include <SFML/System/Clock.hpp>
#include <SFML/Graphics.hpp>
#include "player.h"

class Engine
{
	private:
	// Time handling variables
	const sf::Time frameDelay_ms = sf::milliseconds(1);
	sf::Time timeElapsedFromLastFrame_ms = sf::milliseconds(0);

	// Resolution display values
	const sf::Vector2f resolution = {1000, 800};

	// A regular RenderWindow
	sf::RenderWindow mWindow;

	// Declare a sprite and a Texture for the background
	sf::Sprite mGrassStartSprite;
	sf::Texture mGrassStartTexture;
	sf::Sprite mWaterSprite;
	sf::Texture mWaterTexture;

	// An instance of Player
	Player mPlayer;

	// Private functions for internal use only
	void input();
	void update(float dtAsSeconds);
	void draw();

	public:
	// The Engine constructor
	Engine();

	// start will call all the private functions
	void start();

	void checkWindowBoundCollision();
	void loadTexturesAndSprites();
};