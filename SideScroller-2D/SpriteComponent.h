#pragma once

#include "SFML/Graphics.hpp"

class SpriteComponent {
public:
    SpriteComponent();
    ~SpriteComponent();

    void setImage(const std::string& _path);
    sf::Sprite* getSprite();
private:
    sf::Texture texture;
    sf::Sprite sprite;
};
