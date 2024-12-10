#include "../../include/states/PlayState.hpp"
#include "../../include/states/StateStack.hpp"
#include "../../include/entities/Platform.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

PlayState::PlayState(StateStack& stack)
    : State(stack), mPlayer() {
    // Load the background texture (this will be a static image, not a sprite sheet)
    if (!mBackgroundTexture.loadFromFile("assets/images/Background.png")) {
        std::cerr << "Error loading background image!" << std::endl;
    }
    mBackgroundSprite.setTexture(mBackgroundTexture);

    // test platforms
    mPlatforms.emplace_back(150.0f, 500.0f, 200.0f, 20.0f);
    mPlatforms.emplace_back(400.0f, 450.0f, 200.0f, 20.0f);
}

void PlayState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Escape) {
                // Pause (push pause state)
                mStack.pushState(2);
            }
        }
    }

    mPlayer.handleInput();
}

void PlayState::update(sf::Time dt) {
    mPlayer.update(dt, mPlatforms);
}

void PlayState::render(sf::RenderWindow& window) {
    // Scale the sprite to fit the entire window size while maintaining the aspect ratio
    sf::Vector2u textureSize = mBackgroundTexture.getSize();
    float textureAspect = static_cast<float>(textureSize.x) / static_cast<float>(textureSize.y);
    float windowAspect = static_cast<float>(window.getSize().x) / static_cast<float>(window.getSize().y);

    float scaleX = 1.0f;
    float scaleY = 1.0f;

    // If the window aspect ratio is greater than the texture's aspect ratio, scale by width
    if (windowAspect > textureAspect) {
        scaleX = static_cast<float>(window.getSize().x) / static_cast<float>(textureSize.x);
        scaleY = scaleX; // Maintain aspect ratio
    }
    else { // Otherwise, scale by height
        scaleY = static_cast<float>(window.getSize().y) / static_cast<float>(textureSize.y);
        scaleX = scaleY; // Maintain aspect ratio
    }

    mBackgroundSprite.setScale(scaleX, scaleY);

    // Render the static background sprite
    window.draw(mBackgroundSprite);

    for (const auto& platform : mPlatforms) {
        window.draw(platform.getShape());
    }

    // Render the player (and other entities later)
    mPlayer.render(window);
}
