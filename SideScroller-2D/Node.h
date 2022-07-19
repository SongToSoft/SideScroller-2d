#pragma once

#include "SFML/Graphics.hpp"

#include "TransformComponent.h"
#include "SpriteComponent.h"

enum ENodeType {
	NODE,
	PLAYER,
	BIRD,
	BOMBER,
	FIGHTER
};

class Node {
public:
	Node();
	virtual ~Node();

	TransformComponent* getTransformComponent();
	SpriteComponent* getSpriteComponent();
	std::vector<Node*> getChilds();
	ENodeType getNodeType();

	virtual void draw(sf::RenderWindow& window);
	virtual void update(const float deltaTime);

	bool checkExitBehindScreen(sf::RenderWindow& window);
	void checkCollision(Node* node);

	void hit();
	bool getHit();
protected:
	TransformComponent* transformComponent;
	SpriteComponent* spriteComponent;
	std::vector<Node*> childs;

	bool isHit = false;
	ENodeType type;
};