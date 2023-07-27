#include "Enemy.h"

Enemy::Enemy() {
    // Default constructor, the sprite will be uninitialized until a texture is set.
}

Enemy::Enemy(sf::Texture& texture) {
    // Constructor that takes a texture as an argument and sets up the sprite.
    this->circleSprite.setTexture(texture);
    // Adjust the size and origin of the sprite if necessary.
    this->circleSprite.setScale(0.3f, 0.3f);
    this->circleSprite.setOrigin(sf::Vector2f(this->circleSprite.getLocalBounds().width / 2, this->circleSprite.getLocalBounds().height / 2));
}

const sf::Vector2f& Enemy::getPosition() const {
    // Get the position of the enemy sprite.
    return this->circleSprite.getPosition();
}

const sf::FloatRect Enemy::getGlobalBounds() const {
    // Get the global bounding rectangle of the enemy sprite.
    return this->circleSprite.getGlobalBounds();
}

void Enemy::setPosition(float x, float y) {
    // Set the position of the enemy sprite.
    this->circleSprite.setPosition(x, y);
}

void Enemy::move(float offsetX, float offsetY) {
    // Move the enemy sprite by the specified offsets.
    this->circleSprite.move(offsetX, offsetY);
}

void Enemy::draw(sf::RenderTarget& target) const {
    // Draw the enemy sprite on the given target (usually the game window).
    target.draw(this->circleSprite);
}
