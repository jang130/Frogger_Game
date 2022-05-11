#include "engine.h"

Engine::Engine()
{
	// Create main game window
	mWindow.create(sf::VideoMode(resolution.x, resolution.y), "Frogger Game");

	// Load the background into the texture
	mBackgroundTexture.loadFromFile("textures/background.jpeg");

	// Associate the background sprite with the texture
	mBackgroundSprite.setTexture(mBackgroundTexture);

	// Set player start position
	sf::Vector2f playerPosition{(resolution.x - mPlayer.getWidth()) / 2, resolution.y - mPlayer.getHeight()};
	mPlayer.setPosition(playerPosition);
}

void Engine::start()
{
	// clock is for speed calculations
	// clock_frames is to measure when display new frame
	sf::Clock clock;
	sf::Clock clock_frames;

	while(mWindow.isOpen())
	{
		sf::Event event;
		while(mWindow.pollEvent(event))
		{
			switch(event.type)
			{
				case sf::Event::Closed:
					mWindow.close();
					break;
				case sf::Event::KeyPressed:
					input();
					break;
				case sf::Event::KeyReleased:
					input();
			}
		}

		// Restart the clock and save the elapsed time into dt
		sf::Time dt = clock.restart();

		// Make a fraction from the delta time
		float dtAsSeconds = dt.asSeconds();
		update(dtAsSeconds);
		checkWindowBoundCollision();
		// check time elapsed for frame displaying
		timeElapsedFromLastFrame_ms = clock_frames.getElapsedTime();
		if(timeElapsedFromLastFrame_ms >= frameDelay_ms)
		{
			clock_frames.restart();
			draw();
		}
	}
}

void Engine::input()
{
	// Handle the player quitting
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		mWindow.close();
	}

	// Handle the player moving
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		mPlayer.moveLeft();
	}
	else
	{
		mPlayer.stopLeft();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		mPlayer.moveRight();
	}
	else
	{
		mPlayer.stopRight();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		mPlayer.moveUp();
	}
	else
	{
		mPlayer.stopUp();
	}

	if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		mPlayer.moveDown();
	}
	else
	{
		mPlayer.stopDown();
	}
}

void Engine::update(float dtAsSeconds)
{
	mPlayer.update(dtAsSeconds);
}

void Engine::draw()
{
	// Rub out the last frame
	mWindow.clear(sf::Color::White);

	// Draw the background
	mWindow.draw(mBackgroundSprite);
	mWindow.draw(mPlayer.getSprite());

	// Show everything we have just drawn
	mWindow.display();
}

void Engine::checkWindowBoundCollision()
{
	if(mPlayer.getPosition().x < 0)
	{
		sf::Vector2f newPos = {0, mPlayer.getPosition().y};
		mPlayer.setPosition(newPos);
	}
	else if(mPlayer.getPosition().x + mPlayer.getWidth() > resolution.x)
	{
		sf::Vector2f newPos = {resolution.x - mPlayer.getWidth(), mPlayer.getPosition().y};
		mPlayer.setPosition(newPos);
	}

	if(mPlayer.getPosition().y < 0)
	{
		sf::Vector2f newPos = {mPlayer.getPosition().x, 0};
		mPlayer.setPosition(newPos);
	}
	else if(mPlayer.getPosition().y + mPlayer.getHeight() > resolution.y)
	{
		sf::Vector2f newPos = {mPlayer.getPosition().x, resolution.y - mPlayer.getHeight()};
		mPlayer.setPosition(newPos);
	}

}