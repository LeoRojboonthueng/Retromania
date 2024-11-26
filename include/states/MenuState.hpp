#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../core/State.hpp"

class MenuState : public State {
public:
    MenuState(StateStack& stack);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mStartOption;
    sf::Text mExitOption;

    int mSelectedOption;
};

#endif
