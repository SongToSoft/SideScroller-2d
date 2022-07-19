#pragma once

#include "Node.h"

class Bullet : public Node {
public:
	Bullet();
	~Bullet();

	void update(const float deltaTime);
	void reverseDirection();
private:
	sf::Vector2f speed = { 0.9f, 0.15f };
	sf::Vector2f direction = { 1.0, 1.0 };
};