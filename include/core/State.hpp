#ifndef STATE_HPP
#define STATE_HPP

#include <SFML/Graphics.hpp>

class StateStack;

class State {
public:
    explicit State(StateStack& stack, sf::RenderWindow& window);
    virtual ~State() = default;

    virtual void handleInput(sf::RenderWindow& window) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;

protected:
    StateStack& mStack;
    sf::RenderWindow& mWindow;
};

#endif
