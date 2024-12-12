#include "../../include/states/PlayState.hpp"
#include "../../include/states/StateStack.hpp"
#include "../../include/entities/Platform.hpp"
#include "../../include/entities/Enemy.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

PlayState::PlayState(StateStack& stack, sf::RenderWindow& window)
    : State(stack, window), mPlayer(), mView(sf::FloatRect(0, 0, 800, 600)), mPaused(true), mFirstLoad(true), mCurrentLevel(0) {
    // Load the background texture (this will be a static image, not a sprite sheet)
    if (!mBackgroundTexture.loadFromFile("assets/images/Background.png")) {
        std::cerr << "Error loading background image!" << std::endl;
    }
    mBackgroundTexture.setRepeated(true);
    mBackgroundSprite.setTexture(mBackgroundTexture);

    // platforms, enemies, endBlock
    mLevels = {
        {
            { {170.0f, 500.0f, 200.0f, 20.0f}, {400.0f, 450.0f, 200.0f, 20.0f} },
            { {600.0f, 450.0f}, {900.0f, 450.0f} },
            { 1000.0f, 500.0f, 50.0f, 50.0f }
        },
        {
            { {170.0f, 500.0f, 200.0f, 20.0f}, {400.0f, 450.0f, 200.0f, 20.0f}, {640.0f, 400.0f, 200.0f, 20.0f} },
            { {600.0f, 450.0f}, {900.0f, 450.0f} },
            { 1500.0f, 500.0f, 50.0f, 50.0f }
        }
    };

    loadLevel(mCurrentLevel);
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

    for (auto& enemy : mEnemies) {
        enemy.update(dt, playerPosition);
    }

    checkEndBlockCollision();
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

    for (auto& enemy : mEnemies) {
		window.draw(enemy.getSprite());
    }

    window.draw(mEndBlock);
}

void PlayState::onEnter() {
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
	mPaused = true;
    mSavedView = mView;
    mSavedPlayerPosition = mPlayer.getPosition();
	mView = sf::View(sf::FloatRect(0, 0, 800, 600));
	mView.setCenter(mView.getSize().x / 2.0f, mView.getSize().y / 2.0f);
}

void PlayState::loadLevel(int levelIndex) {
    if (levelIndex < 0 || levelIndex >= mLevels.size()) {
        std::cerr << "Invalid level index!" << std::endl;
        return;
    }

    const Level& level = mLevels[levelIndex];

    mPlatforms.clear();
    for (const auto& platformRect : level.platforms) {
        mPlatforms.emplace_back(platformRect.left, platformRect.top, platformRect.width, platformRect.height);
    }

    mEnemies.clear();
    for (const auto& enemyPos : level.enemies) {
        mEnemies.emplace_back(enemyPos.x, enemyPos.y, 100.0f, 100.0f);
    }

    mEndBlock.setSize(sf::Vector2f(level.endBlock.width, level.endBlock.height));
    mEndBlock.setPosition(level.endBlock.left, level.endBlock.top);
    mEndBlock.setFillColor(sf::Color::Green);
}

void PlayState::checkEndBlockCollision() {
    if (mPlayer.getBounds().intersects(mEndBlock.getGlobalBounds())) {
        mCurrentLevel++;
        if (mCurrentLevel < mLevels.size()) {
            loadLevel(mCurrentLevel);
            mPlayer.setPosition(sf::Vector2f(50.0f, mPlayer.getPosition().y));
        }
        else {
            std::cout << "All levels completed!" << std::endl;
            // show a win screen or smthing?
            mCurrentLevel = 0;
            loadLevel(mCurrentLevel);
            mPlayer.setPosition(sf::Vector2f(50.0f, mPlayer.getPosition().y));
        }
    }
}