#include <SFML/Graphics.hpp>
#include <memory>

class Enemy
{
	private:
	sf::Vector2f mPosition;
	sf::Vector2f mSize;

	sf::Texture mTexture;
	sf::Sprite mSprite;

	float mSpeed;

	public:
	Enemy(std::string textureDir, unsigned int speed);

	void setPosition(sf::Vector2f &pos);
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;

	void update(float elapsedTime);
};

class CarEnemy : public Enemy
{
    using Enemy::Enemy;
};

struct Enemies
{
    const unsigned int enemiesNumberInLine[3] = {3, 4, 5};
	std::vector<std::shared_ptr<CarEnemy>> carEnemiesLine1;
};