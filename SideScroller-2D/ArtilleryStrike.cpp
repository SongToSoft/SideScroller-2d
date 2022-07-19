#include "ArtilleryStrike.h"

#define STRIKE_SIZE {18, 34}
#define LOW_SPEED -1
#define HIGH_SPEED 1


ArtilleryStrike::ArtilleryStrike() {
	transformComponent->setSize(STRIKE_SIZE);
	spriteComponent->setImage("Sprites\\artilleryStrike.png");
	transformComponent->setPosition({ static_cast<float>(400 + rand() % 1100), -100 });
	speed.x = LOW_SPEED + static_cast<float>(rand()) * static_cast<float>(HIGH_SPEED - LOW_SPEED) / RAND_MAX;
}

ArtilleryStrike::~ArtilleryStrike() {
}

void ArtilleryStrike::update(const float deltaTime) {
	auto position = transformComponent->getPosition();
	transformComponent->setPosition({ position.x + (speed.x * deltaTime),
									  position.y + (speed.y * deltaTime) });
}
