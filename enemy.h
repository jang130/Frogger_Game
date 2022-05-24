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

class LogEnemy : public Enemy
{
    using Enemy::Enemy;
};

struct Enemies
{
	const unsigned int carEnemiesLinesPlacementY[5] = {110, 180, 250, 320, 390};
    const unsigned int carEnemiesNumberInLine[5] = {3, 4, 3, 3, 3};
	std::vector<std::vector<std::shared_ptr<CarEnemy>>> carEnemies;
	std::vector<std::string> carTexturesForLines = {"textures/car1.png", "textures/car2.png", "textures/car3.png", "textures/car4.png", "textures/car5.png"};
	std::vector<int> carSpeedsForLines = {100, -150, 200, 300, -50};

	const unsigned int logEnemiesLinesPlacementY[1] = {550};
    const unsigned int logEnemiesNumberInLine[1] = {5};
	std::vector<std::vector<std::shared_ptr<LogEnemy>>> logEnemies;
	std::vector<std::string> logTexturesForLines = {"textures/log1.png"};
	std::vector<int> logSpeedsForLines = {20};
};