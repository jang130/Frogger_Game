#include "player.h"

Player::Player()
{
	// How fast does Player move?
	mSpeed = 400;

	// Associate a texture with the sprite
	mTexture.loadFromFile("textures/frog_player.png");
    mTextureRight.loadFromFile("textures/frog_right.png");
    mTextureLeft.loadFromFile("textures/frog_left.png");
	mSprite.setTexture(mTexture);
}

void Player::setPosition(sf::Vector2f &pos)
{
	mPosition = pos;
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
        mSprite.setTexture(mTexture);
		mPosition.y -= mSpeed * elapsedTime;
	}

	if(mDownPressed)
	{
        mSprite.setTexture(mTexture);
		mPosition.y += mSpeed * elapsedTime;
	}

	// Now move the sprite to its new position
	mSprite.setPosition(mPosition);
}