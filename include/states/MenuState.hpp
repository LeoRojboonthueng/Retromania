#ifndef MENUSTATE_HPP
#define MENUSTATE_HPP

#include "../core/State.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public State {
public:
    explicit MenuState(StateStack& stack, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;
	void updateBackgroundScale();

private:
    sf::Texture mBackgroundTexture;  // For background image
    sf::Sprite mBackgroundSprite;   // Sprite for background image

    sf::Font mFont;
    sf::Text mTitle;
    sf::Text mStartOption;
    sf::Text mExitOption;
	sf::Text mSettingsOption;

    int mSelectedOption; // Tracks which menu option is selected
};

#endif
