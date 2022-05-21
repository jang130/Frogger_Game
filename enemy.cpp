#include <iostream>
#include "enemy.h"
#include "canNotLoadTexture.h"

Enemy::Enemy(std::string textureDir, float speed)
{
	// How fast does Player move?
	mSpeed = speed;

	// Associate a texture with the sprite
	if(!mTexture.loadFromFile(textureDir))
	{
		throw CanNotLoadTexture();
	}
	mTexture.setRepeated(false);
	mSprite.setTexture(mTexture);
	mSize.x = mSprite.getTexture()->getSize().x * mSprite.getScale().x,
	mSize.y = mSprite.getTexture()->getSize().y * mSprite.getScale().y;
}

sf::Sprite Enemy::getSprite() const
{
	return mSprite;
}

void Enemy::setPosition(sf::Vector2f &pos)
{
	mPosition = pos;
	mSprite.setPosition(pos);
}

unsigned int Enemy::getHeight() const
{
	return mSize.y;
}

unsigned int Enemy::getWidth() const
{
	return mSize.x;
}

sf::Vector2f Enemy::getPosition() const
{
	return mPosition;
}

int Enemy::getSpeed() const
{
	return mSpeed;
}

void Enemy::update(float elapsedTime)
{
	mPosition.x += mSpeed * elapsedTime;
	mSprite.setPosition(mPosition);
}