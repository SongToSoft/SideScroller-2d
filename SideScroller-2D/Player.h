#pragma once

#include "Shooter.h"

class Player : public Shooter {
public:
	Player();
	~Player();

	void update(const float deltaTime);
private:
	void shoot();

	float offset;
	float speed;

	sf::Clock clock;
};