#include "../../include/states/MenuState.hpp"
#include "../../include/states/StateStack.hpp"
#include <SFML/Graphics.hpp>
#include <iostream> // For logging

MenuState::MenuState(StateStack& stack)
    : State(stack), mSelectedOption(0) {
    // Load the menu background image
    if (!mBackgroundTexture.loadFromFile("assets/images/menu_background.png")) {
        std::cerr << "Error: Failed to load menu background image!\n";
    }
    else {
        mBackgroundSprite.setTexture(mBackgroundTexture);

        // Scale the background to fit the window
        sf::Vector2u windowSize = sf::Vector2u(800, 600); // Replace with dynamic size if needed
        sf::Vector2u textureSize = mBackgroundTexture.getSize();
        float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
        float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

        mBackgroundSprite.setScale(scaleX, scaleY);
    }

    // Load font
    if (!mFont.loadFromFile("assets/fonts/Roboto.ttf")) {
        std::cerr << "Error: Failed to load font 'Roboto.ttf'. Please ensure it exists in 'assets/fonts/'.\n";
    }

    // Title
    mTitle.setFont(mFont);
    mTitle.setString("Retromania");
    mTitle.setCharacterSize(64);
    mTitle.setFillColor(sf::Color::White);
    mTitle.setPosition(200, 100);

    // Menu Options
    mStartOption.setFont(mFont);
    mStartOption.setString("Start Game");
    mStartOption.setCharacterSize(32);
    mStartOption.setFillColor(sf::Color::Green); // Default selected
    mStartOption.setPosition(200, 250);

    mExitOption.setFont(mFont);
    mExitOption.setString("Exit");
    mExitOption.setCharacterSize(32);
    mExitOption.setFillColor(sf::Color::White);
    mExitOption.setPosition(200, 300);
}

void MenuState::handleInput(sf::RenderWindow& window) {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }
        if (event.type == sf::Event::KeyPressed) {
            if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::Down) {
                // Toggle between menu options
                mSelectedOption = 1 - mSelectedOption;
                mStartOption.setFillColor(mSelectedOption == 0 ? sf::Color::Green : sf::Color::White);
                mExitOption.setFillColor(mSelectedOption == 1 ? sf::Color::Green : sf::Color::White);
            }
            if (event.key.code == sf::Keyboard::Enter) {
                if (mSelectedOption == 0) {
                    // Transition to PlayState
                    mStack.pushState(1); // Use proper state ID or enum
                }
                else if (mSelectedOption == 1) {
                    // Close game
                    window.close();
                }
            }
        }
    }
}

void MenuState::update(sf::Time dt) {
    // Placeholder for future animations or transitions
}

void MenuState::render(sf::RenderWindow& window) {
    // Draw the background
    window.draw(mBackgroundSprite);

    // Draw menu elements
    window.draw(mTitle);
    window.draw(mStartOption);
    window.draw(mExitOption);
}
