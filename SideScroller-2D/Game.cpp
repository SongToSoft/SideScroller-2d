#include "Game.h"

#include <fstream>

#include "Fighter.h"
#include "Player.h"
#include "Bomber.h"
#include "Bird.h"

#define WINDOW_WIDTH 1200
#define WINDOW_HEIGHT 600

#define SKY_BLUE_COLOR sf::Color(135, 206, 235)
#define GROUND_POSITION {0, 530}

#define START_SPAWN_TIME 3000
#define SPAWN_TIME_STEP 50
#define MINIMAL_SPAWN_TIME 1000

#define BIRD_SPAWN_CHANCE 10
#define BOMBER_SPAWN_CHANCE 45
#define FIGHTRE_SPAWN_CHANCE 80

int Game::currentScore = 0;
int Game::highScore = 0;
sf::Text Game::currentScoreText;
sf::Text Game::highScoreText;
sf::RenderWindow Game::window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Side Scrolled 2D");

Game::Game() {
}

Game::~Game() {
	clear();
}

void Game::start() {
	readHighScore();
	init();

	ground = new Node();
	ground->getSpriteComponent()->setImage("Sprites\\ground.png");
	ground->getTransformComponent()->setPosition(GROUND_POSITION);

	sky = new Node();
	sky->getSpriteComponent()->setImage("Sprites\\sky.png");
	sky->getTransformComponent()->setPosition({ 0, 0 });
	enemySpawnClock.restart();

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}
		update();
		draw();
	}
}

void Game::increaseScore() {
	++currentScore;
	currentScoreText.setString("Score: " + std::to_string(currentScore));
}

sf::RenderWindow* Game::getWindow() {
	return &window;
}

void Game::init() {
	currentScore = 0;

	font.loadFromFile("Fonts\\Aire Exterior.ttf");
	highScoreText.setFont(font);
	highScoreText.setString("High Score: " + std::to_string(highScore));
	highScoreText.setCharacterSize(25);
	highScoreText.setPosition(10, 10);

	currentScoreText = highScoreText;
	currentScoreText.setString("Score: " + std::to_string(currentScore));
	currentScoreText.setPosition(10, 35);

	player = new Player();
	
	spawnTime = START_SPAWN_TIME;
}

void Game::draw() {
	window.clear(SKY_BLUE_COLOR);

	sky->draw(window);
	player->draw(window);
	for (auto enemy : enemyes) {
		if (enemy) {
			enemy->draw(window);
		}
	}
	for (auto strike : strikes) {
		if (strike) {
			strike->draw(window);
		}
	}
	ground->draw(window);
	window.draw(highScoreText);
	window.draw(currentScoreText);

	window.display();
}

void Game::update() {
	float time = static_cast<float>(deltaClock.getElapsedTime().asMicroseconds());
	time /= 3000;
	deltaClock.restart();
	player->update(time);
	if (player->getHit()) {
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
			setHighScore();
			clear();
			init();
		}
		return;
	}
	player->checkCollision(ground);
	for (auto enemy : enemyes) {
		if (enemy->checkExitBehindScreen(window)) {
			enemyes.erase(std::remove(enemyes.begin(), enemyes.end(), enemy), enemyes.end());
			delete enemy;
		}
		else {
			player->checkCollision(enemy);
			if (enemy->getNodeType() != ENodeType::BIRD) {
				player->checkBulletCollision(enemy);
				if (enemy->getNodeType() == ENodeType::FIGHTER) {
					for (auto bullet : enemy->getChilds()) {
						if (bullet) {
							player->checkCollision(bullet);
						}
					}
				}
			}
			enemy->update(time);
		}
	}

	for (auto strike : strikes) {
		if (strike->checkExitBehindScreen(window)) {
			strikes.erase(std::remove(strikes.begin(), strikes.end(), strike), strikes.end());
			delete strike;
		}
		else {
			player->checkCollision(strike);
			for (auto enemy : enemyes) {
				if (enemy) {
					strike->checkCollision(enemy);
				}
			}
			strike->update(time);
		}
	}

	time = static_cast<float>(enemySpawnClock.getElapsedTime().asMilliseconds());
	if (time >= spawnTime) {
		spawnEnemy();
		enemySpawnClock.restart();
	}
}

void Game::spawnEnemy() {
	auto chance = rand() % 100;
	if (chance < BIRD_SPAWN_CHANCE) {
		Bird* bird = new Bird();
		enemyes.push_back(bird);
	} else if (chance < BOMBER_SPAWN_CHANCE) {
		Bomber* bomber = new Bomber();
		enemyes.push_back(bomber);
	} else if (chance < FIGHTRE_SPAWN_CHANCE) {
		Fighter* fighter = new Fighter();
		enemyes.push_back(fighter);
	} else {
		ArtilleryStrike* strike = new ArtilleryStrike();
		strikes.push_back(strike);
	}
	if (spawnTime > MINIMAL_SPAWN_TIME) {
		spawnTime -= SPAWN_TIME_STEP;
	}
}

void Game::clear() {
	delete player;
	for (auto enemy : enemyes) {
		if (enemy) {
			delete enemy;
		}
	}
	enemyes.clear();
	for (auto strike : strikes) {
		if (strike) {
			delete strike;
		}
	}
	strikes.clear();
}

void Game::readHighScore() {
	std::ifstream file("HighScore.txt", std::ifstream::in);
	if (file.is_open())
	{
		std::string line;
		std::getline(file, line);
		highScore = atoi(line.c_str());
		file.close();

		highScoreText.setString("High Score: " + std::to_string(highScore));
	}
}

void Game::setHighScore() {
	if (currentScore > highScore)
	{
		highScore = currentScore;
		std::ofstream file("HighScore.txt", std::ofstream::out);
		if (file.is_open())
		{
			file.clear();
			file << currentScore;
			file.close();
		}
	}
}