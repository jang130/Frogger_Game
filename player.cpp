#include "player.h"
#include <iostream>

Player::Player()
{
	// How fast does Player move?
	mSpeed = 300;

	mLeftPressed = false;
	mRightPressed = false;
	mDownPressed = false;
	mUpPressed = false;

	// Associate a texture with the sprite
	if(!mTextureBack.loadFromFile("textures/frog_back.png"))
	{
		throw CanNotLoadTexture();
	}
	if(!mTextureRight.loadFromFile("textures/frog_right.png"))
	{
		throw CanNotLoadTexture();
	}
	if(!mTextureLeft.loadFromFile("textures/frog_left.png"))
	{
		throw CanNotLoadTexture();
	}
	if(!mTextureFront.loadFromFile("textures/frog_front.png"))
	{
		throw CanNotLoadTexture();
	}
	mSprite.setTexture(mTextureBack);

	mSize.x = mSprite.getTexture()->getSize().x * mSprite.getScale().x,
	mSize.y = mSprite.getTexture()->getSize().y * mSprite.getScale().y;
}

void Player::setPosition(sf::Vector2f &pos)
{
	mPosition = pos;
	mSprite.setPosition(mPosition);
}

sf::Sprite Player::getSprite()
{
	return mSprite;
}

void Player::moveLeft()
{
	mLeftPressed = true;
}

void Player::moveRight()
{
	mRightPressed = true;
}

void Player::stopLeft()
{
	mLeftPressed = false;
}

void Player::stopRight()
{
	mRightPressed = false;
}

void Player::moveUp()
{
	mUpPressed = true;
}

void Player::moveDown()
{
	mDownPressed = true;
}

void Player::stopUp()
{
	mUpPressed = false;
}

void Player::stopDown()
{
	mDownPressed = false;
}

unsigned int Player::getHeight() const
{
	return mSize.y;
}

unsigned int Player::getWidth() const
{
	return mSize.x;
}

sf::Vector2f Player::getPosition() const
{
	return mPosition;
}

// Move Player based on the input this frame,
// the time elapsed, and the speed
void Player::update(float elapsedTime)
{
	if(mRightPressed)
	{
		mSprite.setTexture(mTextureRight);
		mPosition.x += mSpeed * elapsedTime;
	}

	if(mLeftPressed)
	{
		mSprite.setTexture(mTextureLeft);
		mPosition.x -= mSpeed * elapsedTime;
	}

	if(mUpPressed)
	{
		mSprite.setTexture(mTextureBack);
		mPosition.y -= mSpeed * elapsedTime;
	}

	if(mDownPressed)
	{
		mSprite.setTexture(mTextureFront);
		mPosition.y += mSpeed * elapsedTime;
	}

	// if(mSprite.getGlobalBounds().intersects())

	// Now move the sprite to its new position
	mSprite.setPosition(mPosition);
}

void Player::movePositionWithLog(float elapsedTime)
{
	mPosition.x += getMoveWithLogSpeed() * elapsedTime;
	mSprite.setPosition(mPosition);
}

void Player::setMoveWithLog(double speed)
{
	moveWithLog = speed;
}

double Player::getMoveWithLogSpeed()
{
	return moveWithLog;
}

bool Player::die(sf::Vector2f newPos)
{
	if(getLives() == 1)
	{
		setLives(0);
		return false;
	}
	setLives(getLives() - 1);
	setPosition(newPos);
	return true;
}

unsigned int Player::getLives() const
{
	return lives;
}

void Player::setLives(unsigned int newLives)
{
	lives = newLives;
}