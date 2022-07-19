#include "Player.h"
#include "Game.h"

#define PLAYER_POSITION {200, 300}
#define PLAYER_SIZE {100, 50}
#define PLAYER_SPEED 0.5f
#define CRASH_HEIGHT 570
#define RATE_FIRE 1.5

Player::Player() {
	transformComponent->setSize(PLAYER_SIZE);
	transformComponent->setPosition(PLAYER_POSITION);
	spriteComponent->setImage("Sprites\\airplane.png");

	offset = transformComponent->getSize().y / 2;
	speed = PLAYER_SPEED;
	type = ENodeType::PLAYER;
}

Player::~Player() {
}

void Player::update(const float deltaTime) {
	if (!isHit) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(*Game::getWindow());
		auto mouseVerticalPosition = static_cast<float>(mousePosition.y) - offset;
		auto playerVerticalPosition = transformComponent->getPosition().y;

		if (mouseVerticalPosition > playerVerticalPosition) {
			transformComponent->setPositionY(playerVerticalPosition + speed * deltaTime);
		}
		else {
			if (playerVerticalPosition > 0) {
				transformComponent->setPositionY(playerVerticalPosition - speed * deltaTime);
			}
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			auto fireTime = static_cast<float>(clock.getElapsedTime().asSeconds());
			if (fireTime > RATE_FIRE) {
				shoot();
				clock.restart();
			}
		}
	}
	else {
		if (transformComponent->getPosition().y + transformComponent->getSize().y < CRASH_HEIGHT) {
			transformComponent->setPositionY(transformComponent->getPosition().y + speed * deltaTime);
		}
	}
	Shooter::update(deltaTime);
}

void Player::shoot() {
	Bullet* bullet = new Bullet();
	bullet->getTransformComponent()->setPosition({ transformComponent->getPosition().x + transformComponent->getSize().x,
		                                           transformComponent->getPosition().y + offset });
	childs.push_back(bullet);
}