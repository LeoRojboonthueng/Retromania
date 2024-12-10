#include "../../include/states/PlayState.hpp"
#include "../../include/states/StateStack.hpp"
#include "../../include/entities/Platform.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

PlayState::PlayState(StateStack& stack, sf::RenderWindow& window)
    : State(stack, window), mPlayer() {
    // Load the background texture (this will be a static image, not a sprite sheet)
    if (!mBackgroundTexture.loadFromFile("assets/images/Background.png")) {
        std::cerr << "Error loading background image!" << std::endl;
    }
    mBackgroundTexture.setRepeated(true);
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
    sf::Vector2u textureSize = mBackgroundTexture.getSize();
    float windowHeight = static_cast<float>(600);
    float scaleY = windowHeight / static_cast<float>(textureSize.y);

    mBackgroundSprite.setScale(scaleY, scaleY);

    // Set the texture rect to repeat horizontally
    sf::IntRect textureRect(0, 0, static_cast<int>(800 / scaleY), textureSize.y);
    mBackgroundSprite.setTextureRect(textureRect);

    // Render the static background sprite
    window.draw(mBackgroundSprite);

    for (const auto& platform : mPlatforms) {
        window.draw(platform.getShape());
    }

    mPlayer.render(window);
}
