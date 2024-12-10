#include "../../include/entities/Platform.hpp"

Platform::Platform(float x, float y, float width, float height) {
    mShape.setPosition(x, y);
    mShape.setSize(sf::Vector2f(width, height));
    mShape.setFillColor(sf::Color::Green);
}

sf::RectangleShape& Platform::getShape() {
    return mShape;
}

const sf::RectangleShape& Platform::getShape() const {
    return mShape;
}