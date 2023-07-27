#pragma once

#include <SFML/Graphics.hpp>

class Enemy {
private:
    sf::Sprite circleSprite;

public:
    // Constructors
    Enemy();
    Enemy(sf::Texture& texture);

    // Destructor
    virtual ~Enemy() {}

    // Getters
    const sf::Vector2f& getPosition() const;
    const sf::FloatRect getGlobalBounds() const;

    // Setters
    void setPosition(float x, float y);
    void move(float offsetX, float offsetY);

    // Render the enemy sprite on the given target
    void draw(sf::RenderTarget& target) const;
};
