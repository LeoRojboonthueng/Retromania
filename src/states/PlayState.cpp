#include "../../include/states/PlayState.hpp"
#include "../../include/states/StateStack.hpp"
#include "../../include/entities/Platform.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

PlayState::PlayState(StateStack& stack, sf::RenderWindow& window)
    : State(stack, window), mPlayer(), mView(sf::FloatRect(0, 0, 800, 600)), mPaused(true), mFirstLoad(true) {
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
	if (mPaused) {
		return;
	}
    mPlayer.update(dt, mPlatforms);

    sf::Vector2f playerPosition = mPlayer.getPosition();
    if (playerPosition.x < 50.0f) {
        playerPosition.x = 50.0f;
        mPlayer.setPosition(playerPosition);
    }
    mView.setCenter(playerPosition.x+150, mView.getSize().y / 2.0f);
    std::cout << "PlayState::update()" << std::endl;
}

void PlayState::render(sf::RenderWindow& window) {
    window.setView(mView);

    if (mPaused) {
        return;
    }

    sf::Vector2u textureSize = mBackgroundTexture.getSize();
    float windowHeight = static_cast<float>(600);
    float scaleY = windowHeight / static_cast<float>(textureSize.y);

    mBackgroundSprite.setScale(scaleY, scaleY);

    float backgroundX = mView.getCenter().x - 400.0f;
    mBackgroundSprite.setPosition(backgroundX, 0);

    sf::IntRect textureRect(static_cast<int>(backgroundX / scaleY), 0, static_cast<int>(800 / scaleY), textureSize.y);
    mBackgroundSprite.setTextureRect(textureRect);

    // Render the static background sprite
    window.draw(mBackgroundSprite);

    for (const auto& platform : mPlatforms) {
        window.draw(platform.getShape());
    }

    mPlayer.render(window);
	std::cout << "PlayState::render()" << std::endl;
}

void PlayState::onEnter() {
	std::cout << "PlayState::onEnter()" << std::endl;
	mPaused = false;
    if (mFirstLoad) {
        mFirstLoad = false;
        mView.setCenter(400.0f, mView.getSize().y / 2.0f); 
        mPlayer.setPosition(sf::Vector2f(50.0f, mPlayer.getPosition().y));
    }
    else {
        mView = mSavedView;
        mPlayer.setPosition(mSavedPlayerPosition);
    }
}

void PlayState::onExit() {
	std::cout << "PlayState::onExit()" << std::endl;
	mPaused = true;
    mSavedView = mView;
    mSavedPlayerPosition = mPlayer.getPosition();
	mView = sf::View(sf::FloatRect(0, 0, 800, 600));
	mView.setCenter(mView.getSize().x / 2.0f, mView.getSize().y / 2.0f);
}