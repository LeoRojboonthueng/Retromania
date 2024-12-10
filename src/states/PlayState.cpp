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
    sf::Vector2u windowSize = window.getSize();
    sf::Vector2u textureSize = mBackgroundTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / 800.0f; // Assuming 800 is the original width
    float scaleY = static_cast<float>(windowSize.y) / 600.0f; // Assuming 600 is the original height

    int repeatCountX = windowSize.x / textureSize.x + 1;
    mBackgroundSprite.setTextureRect(sf::IntRect(0, 0, repeatCountX * textureSize.x, textureSize.y));

    // Scale the background sprite
    mBackgroundSprite.setScale(scaleX, scaleY);

    // Render the static background sprite
    window.draw(mBackgroundSprite);

    for (auto& platform : mPlatforms) {
        platform.getShape().setScale(scaleX, scaleY);
        window.draw(platform.getShape());
    }

    mPlayer.getSprite().setScale(scaleX, scaleY);
    mPlayer.render(window);
}
