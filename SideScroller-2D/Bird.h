#pragma once

#include "Node.h"

class Bird : public Node {
public:
	Bird();
	~Bird();

	void update(const float deltaTime);
private:
	sf::Vector2f speed = { 0.3f, 0.1f };
	sf::Vector2f direction = { -1.0, 1.0 };
	int offset;
	sf::Clock clock;
};