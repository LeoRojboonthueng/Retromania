#ifndef SETTINGSSTATE_HPP
#define SETTINGSSTATE_HPP

#include "../core/State.hpp"
#include <SFML/Graphics.hpp>

class SettingsState : public State {
public:
    explicit SettingsState(StateStack& stack, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mResolutionOption;
    int mSelectedOption;
    std::vector<sf::Vector2u> mResolutions;
};

#endif