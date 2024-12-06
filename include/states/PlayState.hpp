#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "../core/State.hpp"  // Base State class
#include "../states/StateStack.hpp"  // StateStack class
#include "../entities/Player.hpp"  // Player class
#include <SFML/Graphics.hpp>  // SFML graphics library

class PlayState : public State {
public:
    explicit PlayState(StateStack& stack);  // Constructor

    void handleInput(sf::RenderWindow& window) override;  // Handle user input
    void update(sf::Time dt) override;                   // Update game logic
    void render(sf::RenderWindow& window) override;      // Render the scene

private:
    sf::Texture mBackgroundTexture;  // Background texture
    sf::Sprite mBackgroundSprite;    // Sprite for the background

    Player mPlayer;  // Player object
    float mPlayerSpeed = 200.0f;  // Player speed (pixels per second)
};

#endif  // PLAYSTATE_HPP
