#include "Fighter.h"

#define FIGHTER_POSITION {1200, 110}
#define FIGHTER_SIZE {138, 50}
#define FIGHTER_FIRE_RATE 2
#define FIGHTER_OFFSET 100

Fighter::Fighter() {
	transformComponent->setSize(FIGHTER_SIZE);
	sf::Vector2f position = FIGHTER_POSITION;
	offset = FIGHTER_OFFSET;
	position.y += (rand() % offset);
	transformComponent->setPosition(position);
	spriteComponent->setImage("Sprites\\fighter.png");

	type = ENodeType::FIGHTER;
}

Fighter::~Fighter() {
}


void Fighter::update(const float deltaTime) {
	auto position = transformComponent->getPosition();
	if (isHit) {
		transformComponent->setPosition({ position.x - (speed.x * deltaTime),
										  position.y + (speed.y * deltaTime) });
	}
	else {
		auto time = static_cast<float>(clock.getElapsedTime().asSeconds());
		if (time > FIGHTER_FIRE_RATE) {
			direction.y *= -1;
			shoot();
			clock.restart();
		}
		transformComponent->setPosition({ position.x + (speed.x * direction.x * deltaTime),
										  position.y + (speed.y * direction.y * deltaTime) });
	}

	Shooter::update(deltaTime);
}

void Fighter::shoot() {
	Bullet* bullet = new Bullet();
	bullet->getTransformComponent()->setPosition({ transformComponent->getPosition().x,
												   transformComponent->getPosition().y + transformComponent->getSize().y / 2 });
	bullet->reverseDirection();
	childs.push_back(bullet);
}