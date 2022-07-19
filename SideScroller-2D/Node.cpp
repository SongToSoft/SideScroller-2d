#include "Node.h"
#include "Game.h"

Node::Node() {
	transformComponent = new TransformComponent();
	spriteComponent = new SpriteComponent();
}

Node::~Node() {
	delete transformComponent;
	delete spriteComponent;
	for (auto child : childs) {
		delete child;
	}
}

TransformComponent* Node::getTransformComponent() {
	return transformComponent;
}

SpriteComponent* Node::getSpriteComponent() {
	return spriteComponent;
}

std::vector<Node*> Node::getChilds() {
	return childs;
}

ENodeType Node::getNodeType() {
	return type;
}

void Node::draw(sf::RenderWindow& window) {
	auto sprite = spriteComponent->getSprite();
	spriteComponent->getSprite()->setPosition(transformComponent->getPosition());
	window.draw(*sprite);
}

void Node::update(const float deltaTime) {
}

bool Node::checkExitBehindScreen(sf::RenderWindow& window) {
	if ((transformComponent->getPosition().x + transformComponent->getSize().x < 0) ||
		(transformComponent->getPosition().x > window.getSize().x)) {
		return true;
	}
	return false;
}

void Node::checkCollision(Node* node) {
	if (transformComponent->getRect().intersects(node->getTransformComponent()->getRect()) && !node->getHit()) {
		isHit = true;
		if (type != ENodeType::PLAYER) {
			node->hit();
		}
	}
}

void Node::hit() {
	if ((type == ENodeType::BOMBER) || (type == ENodeType::FIGHTER)) {
		Game::increaseScore();
	}
	isHit = true;
}

bool Node::getHit() {
	return isHit;
}