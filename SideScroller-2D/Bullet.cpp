#include "Bullet.h"

#define BULLET_SIZE {31, 10}

Bullet::Bullet() {
	transformComponent->setSize(BULLET_SIZE);
	spriteComponent->setImage("Sprites\\bullet.png");
}

Bullet::~Bullet() {
}

void Bullet::update(const float deltaTime) {
	auto position = transformComponent->getPosition();
	transformComponent->setPosition({ position.x + (direction.x * speed.x * deltaTime),
									  position.y + (direction.y * speed.y * deltaTime) });
}

void Bullet::reverseDirection() {
	direction.x *= -1;
}