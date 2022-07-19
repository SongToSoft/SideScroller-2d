#pragma once

#include "Node.h"

class ArtilleryStrike : public Node {
public:
	ArtilleryStrike();
	~ArtilleryStrike();

	void update(const float deltaTime);
private:
	sf::Vector2f speed = { 0.1f, 0.3f };
};