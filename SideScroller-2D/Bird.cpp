#include "Bird.h"

#define BIRD_POSITION {1200, 350}
#define BIRD_SIZE {33, 36}
#define BIRD_CHANGE_DIRECTION_RATE 2
#define BIRD_OFFSET 100

Bird::Bird() {
	transformComponent->setSize(BIRD_SIZE);
	sf::Vector2f position = BIRD_POSITION;
	offset = BIRD_OFFSET;
	position.y += (rand() % offset);
	transformComponent->setPosition(position);
	spriteComponent->setImage("Sprites\\bird.png");
	type = ENodeType::BIRD;
}

Bird::~Bird() {
}

void Bird::update(const float deltaTime) {
	auto position = transformComponent->getPosition();
	transformComponent->setPosition({ position.x + (speed.x * direction.x * deltaTime),
									  position.y + (speed.y * direction.y * deltaTime)});

	auto time = static_cast<float>(clock.getElapsedTime().asSeconds());
	if (time > BIRD_CHANGE_DIRECTION_RATE) {
		direction.y *= -1;
		clock.restart();
	}
}
