#include <iostream>
#include <memory>
#include "engine.h"
#include "canNotLoadTexture.h"

Engine::Engine()
{
	// Create main game window
	mWindow.create(sf::VideoMode(resolution.x, resolution.y), "Frogger Game");

	// Loads textures and Sprites for backround staff
	loadBackgroundTexturesAndSprites();

	// Sets player initial position
	sf::Vector2f playerPosition{(resolution.x - mPlayer.getWidth()) / 2, resolution.y - mPlayer.getHeight()};
	mPlayer.setPosition(playerPosition);

	sf::Vector2f carPos = {0, resolution.y - 150};
	std::shared_ptr<CarEnemy> newEnemy1 = std::make_shared<CarEnemy>("textures/car1.png", 100);
	std::shared_ptr<CarEnemy> newEnemy2 = std::make_shared<CarEnemy>("textures/car1.png", 100);
	std::shared_ptr<CarEnemy> newEnemy3 = std::make_shared<CarEnemy>("textures/car1.png", 100);
	newEnemy1->setPosition(carPos);
	carPos = {400, resolution.y - 150};
	newEnemy2->setPosition(carPos);
	carPos = {800, resolution.y - 150};
	newEnemy3->setPosition(carPos);

	mEnemies.carEnemiesLine1.push_back(newEnemy1);
	mEnemies.carEnemiesLine1.push_back(newEnemy2);
	mEnemies.carEnemiesLine1.push_back(newEnemy3);
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
	for(std::shared_ptr<CarEnemy> &carEnemyObj: mEnemies.carEnemiesLine1)
	{
		carEnemyObj->update(dtAsSeconds);
	}
}

void Engine::draw()
{
	// Rub out the last frame
	mWindow.clear(sf::Color::White);

	// Draw the background
	mWindow.draw(mGrassStartSprite);
	// mWindow.draw(mWaterSprite);
	mWindow.draw(mPlayer.getSprite());
	for(std::shared_ptr<CarEnemy> &carEnemyObj: mEnemies.carEnemiesLine1)
	{
		mWindow.draw(carEnemyObj->getSprite());
	}

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

	for(std::shared_ptr<CarEnemy> &carEnemyObj: mEnemies.carEnemiesLine1)
	{
		if(carEnemyObj->getPosition().x > resolution.x)
		{
			float xVal = carEnemyObj->getWidth();
			sf::Vector2f newPos = {-xVal, carEnemyObj->getPosition().y};
			carEnemyObj->setPosition(newPos);
		}
	}
	// if(mPlayer.getSprite().getGlobalBounds().intersects(mWaterSprite.getGlobalBounds()))
	// {
	// 	//detect collision into water
	// 	sf::Vector2f newPos = {0, 0};
	// 	mPlayer.setPosition(newPos);
	// }
}

void Engine::loadBackgroundTexturesAndSprites()
{
	// Load the background textures
	if(!mGrassStartTexture.loadFromFile("textures/grass_start.png"))
	{
		throw CanNotLoadTexture();
	}
	mGrassStartTexture.setRepeated(true);
	mGrassStartSprite.setTextureRect(sf::IntRect(0, 0, resolution.x, 100));
	mGrassStartSprite.setTexture(mGrassStartTexture);
	mGrassStartSprite.setPosition(0, resolution.y - 100);

	// mWaterTexture.loadFromFile("textures/water.png");
	// mWaterTexture.setRepeated(true);
	// mWaterSprite.setTextureRect(sf::IntRect(0, 0, resolution.x, 100));
	// mWaterSprite.setTexture(mWaterTexture);
	// mWaterSprite.setPosition(0, resolution.y - 200);
}
