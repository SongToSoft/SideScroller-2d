#pragma once

#include "SFML/Graphics.hpp"

class TransformComponent {
public:
    TransformComponent();
    ~TransformComponent();

    sf::Vector2f getPosition();
    sf::Vector2f getSize();
    sf::FloatRect getRect();

    void setPosition(sf::Vector2f _position);
    void setPositionX(float _X);
    void setPositionY(float _Y);
    void setSize(sf::Vector2f _size);
private:
    sf::Vector2f position;
    sf::Vector2f size;
    sf::Vector2f scale;
};
