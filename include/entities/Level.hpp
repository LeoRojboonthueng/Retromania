#ifndef LEVEL_HPP
#define LEVEL_HPP

#include <vector>
#include <SFML/Graphics.hpp>

struct Level {
    std::vector<sf::FloatRect> platforms;
    std::vector<sf::Vector2f> enemies;
    sf::FloatRect endBlock;
};

#endif