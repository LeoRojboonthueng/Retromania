#ifndef PLATFORM_HPP
#define PLATFORM_HPP

#include <SFML/Graphics.hpp>

class Platform {
public:
    Platform(float x, float y, float width, float height);
    sf::RectangleShape& getShape();
    const sf::RectangleShape& getShape() const;

private:
    sf::RectangleShape mShape;
};

#endif