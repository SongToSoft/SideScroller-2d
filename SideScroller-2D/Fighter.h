#pragma once

#include "Shooter.h"
#include "Bullet.h"

class Fighter : public Shooter {
public:
	Fighter();
	~Fighter();

	void update(const float deltaTime);

private:
	void shoot();

	int offset;
	sf::Vector2f speed = { 0.3f, 0.4f };
	sf::Vector2f direction = { -1.0f, 0.1f };
	sf::Clock clock;
};