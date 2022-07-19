#pragma once

#include "Node.h"

class Shooter : public Node {
public:
	Shooter();
	virtual ~Shooter();

	void draw(sf::RenderWindow& window);
	void update(const float deltaTime);

	void checkBulletCollision(Node* node);
protected:
	virtual void shoot() = 0;
};