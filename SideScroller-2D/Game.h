#pragma once

#include "SFML/Graphics.hpp"

#include "ArtilleryStrike.h"
#include "Player.h"
#include "Node.h"

class Game {
public:
	Game();
	~Game();

	void start();

	static void increaseScore();
	static sf::RenderWindow* getWindow();
private:
	void init();

	void draw();
	void update();

	void spawnEnemy();
	void clear();

	static void readHighScore();
	static void setHighScore();

	static sf::RenderWindow window;
	static sf::Text highScoreText, currentScoreText;

	sf::Font font;
	sf::Clock deltaClock, enemySpawnClock;

	Player* player;
	Node *ground, *sky;
	std::vector<Node*> enemyes;
	std::vector<ArtilleryStrike*> strikes;
	int spawnTime;
	static int currentScore;
	static int highScore;
};