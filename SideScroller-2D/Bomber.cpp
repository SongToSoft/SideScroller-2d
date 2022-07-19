#include "Bomber.h"

#define BOMBER_POSITION {1200, 200}
#define BOMBER_SIZE {75, 25}
#define BOMBER_OFFSET 100

Bomber::Bomber() {
	transformComponent->setSize(BOMBER_SIZE);
	sf::Vector2f position = BOMBER_POSITION;
	offset = BOMBER_OFFSET;
	position.y += (rand() % offset);
	transformComponent->setPosition(position);
	spriteComponent->setImage("Sprites\\bomber.png");
	type = ENodeType::BOMBER;
}

Bomber::~Bomber() {
}

void Bomber::update(const float deltaTime) {
	auto position = transformComponent->getPosition();
	if (isHit) {
		transformComponent->setPosition({ position.x - (speed.x * deltaTime),
										  position.y + (speed.y * deltaTime) });
	}
	else {
		transformComponent->setPosition({ position.x - (speed.x * deltaTime),
										  position.y });
	}
}