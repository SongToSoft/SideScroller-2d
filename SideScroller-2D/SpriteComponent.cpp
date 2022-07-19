#include "SpriteComponent.h"

SpriteComponent::SpriteComponent() {
}

SpriteComponent::~SpriteComponent() {
}

void SpriteComponent::setImage(const std::string& path) {
	if (texture.loadFromFile(path)) {
		sprite = sf::Sprite(texture);
	}
}

sf::Sprite* SpriteComponent::getSprite() {
	sprite = sf::Sprite(texture);
	return &sprite;
}