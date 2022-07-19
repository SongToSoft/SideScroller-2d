#pragma once

#include "Node.h"

class Bomber : public Node {
public:
	Bomber();
	~Bomber();

	void update(const float deltaTime);
private:
	int offset = 150;
	sf::Vector2f speed = { 0.7f, 0.4f };
};