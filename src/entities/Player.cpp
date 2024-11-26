#include "../../include/entities/Player.hpp"
#include <iostream>

// Just for proving rendering worked, need to redo this

Player::Player()
    : mSpeed(200.0f), mVelocity(0.0f, 0.0f) {

    mShape.setSize(sf::Vector2f(50.0f, 50.0f));
    mShape.setFillColor(sf::Color::Cyan);
    mShape.setPosition(50.0f, 50.0f);
}

void Player::handleInput() {
    mVelocity = sf::Vector2f(0.0f, 0.0f);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        mVelocity.x = -mSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        mVelocity.x = mSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        mVelocity.y = -mSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        mVelocity.y = mSpeed;
    }
}

void Player::update(sf::Time dt) {
    mShape.move(mVelocity * dt.asSeconds());
}

void Player::render(sf::RenderWindow& window) {
    window.draw(mShape);
}
