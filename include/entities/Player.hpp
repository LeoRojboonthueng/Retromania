#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>

class Player {
public:
    Player();

    void handleInput();
    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

private:
    sf::RectangleShape mShape;
    sf::Vector2f mVelocity;
    float mSpeed;
};

#endif
