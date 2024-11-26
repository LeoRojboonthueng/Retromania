#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "../core/State.hpp"
#include "../entities/Player.hpp"

class PlayState : public State {
public:
    explicit PlayState(StateStack& stack);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;

private:
    Player mPlayer;
};

#endif
