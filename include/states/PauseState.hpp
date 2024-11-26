#ifndef PAUSESTATE_HPP
#define PAUSESTATE_HPP

#include "../core/State.hpp"

class PauseState : public State {
public:
    PauseState(StateStack& stack);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mResumeOption;
    sf::Text mExitOption;

    int mSelectedOption;
};

#endif
