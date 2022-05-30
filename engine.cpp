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

	createCarEnemies(5);
	createLogEnemies(4);
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
		checkCollision();

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
	mPlayer.movePositionWithLog(dtAsSeconds);
	for(std::vector<std::shared_ptr<CarEnemy>> &line: mEnemies.carEnemies)
	{
		for(std::shared_ptr<CarEnemy> &carEnemyObj: line)
		{
			carEnemyObj->update(dtAsSeconds);
		}
	}

	for(std::vector<std::shared_ptr<LogEnemy>> &line: mEnemies.logEnemies)
	{
		for(std::shared_ptr<LogEnemy> &logEnemyObj: line)
		{
			logEnemyObj->update(dtAsSeconds);
		}
	}
}

void Engine::draw()
{
	// Rub out the last frame
	mWindow.clear(sf::Color::White);

	// Draw the background
	mWindow.draw(mGrassStartSprite);
	mWindow.draw(mGrassMidSprite);
	mWindow.draw(mRoadSprite);
	mWindow.draw(mWaterSprite);

	for(std::vector<std::shared_ptr<LogEnemy>> &line: mEnemies.logEnemies)
	{
		for(std::shared_ptr<LogEnemy> &logEnemyObj: line)
		{
			mWindow.draw(logEnemyObj->getSprite());
		}
	}

	mWindow.draw(mPlayer.getSprite());

	for(std::vector<std::shared_ptr<CarEnemy>> &line: mEnemies.carEnemies)
	{
		for(std::shared_ptr<CarEnemy> &carEnemyObj: line)
		{
			mWindow.draw(carEnemyObj->getSprite());
		}
	}
	// Show everything we have just drawn
	mWindow.display();
}

void Engine::checkCollision()
{
	checkPlayerBoundCollision();

	checkPlayerCarEnemyCollision();

	checkPlayerLogEnemyCollision();

	checkPlayerWaterCollision();
}

void Engine::checkPlayerBoundCollision()
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

void Engine::checkPlayerCarEnemyCollision()
{
	for(std::vector<std::shared_ptr<CarEnemy>> &line: mEnemies.carEnemies)
	{
		for(std::shared_ptr<CarEnemy> &carEnemyObj: line)
		{
			if(carEnemyObj->getSprite().getGlobalBounds().intersects(mPlayer.getSprite().getGlobalBounds()))
			{
				sf::Vector2f newPos = {(resolution.x - mPlayer.getWidth()) / 2, resolution.y - mPlayer.getHeight()};
				mPlayer.setPosition(newPos);
			}
			if(carEnemyObj->getSpeed() > 0)
			{
				if(carEnemyObj->getPosition().x > resolution.x)
				{
					float xVal = carEnemyObj->getWidth();
					sf::Vector2f newPos = {-xVal, carEnemyObj->getPosition().y};
					carEnemyObj->setPosition(newPos);
				}
			}
			else
			{
				if(carEnemyObj->getPosition().x + carEnemyObj->getWidth() < 0)
				{
					sf::Vector2f newPos = {resolution.x, carEnemyObj->getPosition().y};
					carEnemyObj->setPosition(newPos);
				}
			}
		}
	}
}

void Engine::checkPlayerLogEnemyCollision()
{
	mPlayer.setMoveWithLog(0);
	int i = 0;
	for(std::vector<std::shared_ptr<LogEnemy>> &line: mEnemies.logEnemies)
	{
		for(std::shared_ptr<LogEnemy> &logEnemyObj: line)
		{
			if(logEnemyObj->getSprite().getGlobalBounds().intersects(mPlayer.getSprite().getGlobalBounds()))
			{
				mPlayer.setMoveWithLog(mEnemies.logSpeedsForLines[i]);
			}

			if(logEnemyObj->getSpeed() > 0)
			{
				if(logEnemyObj->getPosition().x > resolution.x)
				{
					float xVal = logEnemyObj->getWidth();
					sf::Vector2f newPos = {-xVal, logEnemyObj->getPosition().y};
					logEnemyObj->setPosition(newPos);
				}
			}
			else
			{
				if(logEnemyObj->getPosition().x + logEnemyObj->getWidth() < 0)
				{
					sf::Vector2f newPos = {resolution.x, logEnemyObj->getPosition().y};
					logEnemyObj->setPosition(newPos);
				}
			}
		}
		i++;
	}
}

void Engine::checkPlayerWaterCollision()
{
	if(mPlayer.getMoveWithLogSpeed() == 0)
	{
		if(mWaterSprite.getGlobalBounds().intersects(mPlayer.getSprite().getGlobalBounds()))
		{
			sf::Vector2f newPos = {resolution.x / 2, resolution.y};
			mPlayer.setPosition(newPos);
		}
	}
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

	if(!mGrassMidTexture.loadFromFile("textures/grass_start.png"))
	{
		throw CanNotLoadTexture();
	}
	mGrassMidTexture.setRepeated(true);
	mGrassMidSprite.setTextureRect(sf::IntRect(0, 0, resolution.x, 100));
	mGrassMidSprite.setTexture(mGrassMidTexture);
	mGrassMidSprite.setPosition(0, resolution.y - 480);

	if(!mRoadTexture.loadFromFile("textures/road.png"))
	{
		throw CanNotLoadTexture();
	}
	mRoadTexture.setRepeated(true);
	mRoadSprite.setTextureRect(sf::IntRect(0, 0, resolution.x, 350));
	mRoadSprite.setTexture(mRoadTexture);
	mRoadSprite.setPosition(0, resolution.y - 400);

	if(!mWaterTexture.loadFromFile("textures/water.png"))
	{
		throw CanNotLoadTexture();
	}
	mWaterTexture.setRepeated(true);
	mWaterSprite.setTextureRect(sf::IntRect(0, 0, resolution.x, 270));
	mWaterSprite.setTexture(mWaterTexture);
	mWaterSprite.setPosition(0, 50);
}

void Engine::createCarEnemies(unsigned int linesToCreate)
{
	for(int i = 0; i < linesToCreate; ++i)
	{
		std::vector<std::shared_ptr<CarEnemy>> carEnemyLine;
		mEnemies.carEnemies.push_back(carEnemyLine);
	}
	unsigned int lineNumber = 0;
	for(std::vector<std::shared_ptr<CarEnemy>> &line: mEnemies.carEnemies)
	{
		float xPush = 0;
		for(int i = 0; i < mEnemies.carEnemiesNumberInLine[lineNumber]; ++i)
		{
			sf::Vector2f carPos = {xPush, resolution.y - mEnemies.carEnemiesLinesPlacementY[lineNumber]};
			std::shared_ptr<CarEnemy> newEnemy =
			  std::make_shared<CarEnemy>(mEnemies.carTexturesForLines[lineNumber], mEnemies.carSpeedsForLines[lineNumber]);
			newEnemy->setPosition(carPos);
			line.push_back(newEnemy);
			xPush = xPush + (resolution.x / mEnemies.carEnemiesNumberInLine[lineNumber]);
		}
		lineNumber++;
	}
}

void Engine::createLogEnemies(unsigned int linesToCreate)
{
	for(int i = 0; i < linesToCreate; ++i)
	{
		std::vector<std::shared_ptr<LogEnemy>> logEnemyLine;
		mEnemies.logEnemies.push_back(logEnemyLine);
	}
	unsigned int lineNumber = 0;
	for(std::vector<std::shared_ptr<LogEnemy>> &line: mEnemies.logEnemies)
	{
		float xPush = 0;
		for(int i = 0; i < mEnemies.logEnemiesNumberInLine[lineNumber]; ++i)
		{
			sf::Vector2f logPos = {xPush, resolution.y - mEnemies.logEnemiesLinesPlacementY[lineNumber]};
			std::shared_ptr<LogEnemy> newEnemy =
			  std::make_shared<LogEnemy>(mEnemies.logTexturesForLines[lineNumber], mEnemies.logSpeedsForLines[lineNumber]);
			newEnemy->setPosition(logPos);
			line.push_back(newEnemy);
			xPush = xPush + (resolution.x / mEnemies.logEnemiesNumberInLine[lineNumber]);
		}
		lineNumber++;
	}
}
