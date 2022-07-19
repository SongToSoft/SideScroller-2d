#include "Shooter.h"
#include "Game.h"

Shooter::Shooter() {
}

Shooter::~Shooter() {
}

void Shooter::draw(sf::RenderWindow& window) {
	for (auto& bullet : childs) {
		if (bullet) {
			bullet->draw(window);
		}
	}
	Node::draw(window);
}

void Shooter::update(const float deltaTime) {
	for (auto bullet : childs) {
		if (bullet) {
			if (bullet->checkExitBehindScreen(*Game::getWindow())) {
				childs.erase(std::remove(childs.begin(), childs.end(), bullet), childs.end());
				delete bullet;
			}
			else {
				bullet->update(deltaTime);
			}
		}
	}
}

void Shooter::checkBulletCollision(Node* node) {
	sf::FloatRect nodeRect = node->getTransformComponent()->getRect();
	for (auto bullet : childs) {
		if (nodeRect.intersects(bullet->getTransformComponent()->getRect()) && !node->getHit()) {
			node->hit();
			return;
		}
	}
}
