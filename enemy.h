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
	Enemy(std::string textureDir, float speed);

	void setPosition(sf::Vector2f &pos);
	unsigned int getHeight() const;
	unsigned int getWidth() const;
	sf::Vector2f getPosition() const;
	sf::Sprite getSprite() const;
	int getSpeed() const;

	void update(float elapsedTime);
};

class CarEnemy : public Enemy
{
    using Enemy::Enemy;
};

struct Enemies
{
	const unsigned int enemiesLinesPlacementY[5] = {110, 180, 250, 320, 390};
    const unsigned int enemiesNumberInLine[5] = {3, 4, 3, 3, 3};
	std::vector<std::vector<std::shared_ptr<CarEnemy>>> carEnemies;
	std::vector<std::string> texturesForLines = {"textures/car1.png", "textures/car2.png", "textures/car3.png", "textures/car4.png", "textures/car5.png"};
	std::vector<int> speedsForLines = {100, -150, 200, 300, -50};
};