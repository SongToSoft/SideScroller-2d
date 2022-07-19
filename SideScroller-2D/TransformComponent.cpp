#include "TransformComponent.h"

#define DEFAULT_POSITION {0, 0}
#define DEFAULT_SCALE {1, 1}

TransformComponent::TransformComponent() {
    position = DEFAULT_POSITION;
    scale = DEFAULT_SCALE;
}

TransformComponent::~TransformComponent() {

}

sf::Vector2f TransformComponent::getPosition() {
    return position;
}

sf::Vector2f TransformComponent::getSize() {
    return size;
}

sf::FloatRect TransformComponent::getRect() {
    return { position.x, position.y, size.x, size.y };
}

void TransformComponent::setPosition(sf::Vector2f _position) {
    position = _position;
}

void TransformComponent::setPositionX(float _x) {
    position.x = _x;
}

void TransformComponent::setPositionY(float _y) {
    position.y = _y;
}

void TransformComponent::setSize(sf::Vector2f _size) {
    size = _size;
}


