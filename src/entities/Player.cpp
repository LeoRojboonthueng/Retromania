#include "../../include/entities/Player.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

// Just for proving rendering worked, need to redo this

Player::Player()
    : mSpeed(200.0f), mVelocity(0.0f, 0.0f), mCurrentFrame(0), mFrameTime(sf::seconds(0.2f)), mGravity(1500.0f), mGroundLevel(450.0f), mMaxJumpHeight(150.0f) {

    if (!mTexture.loadFromFile("assets/images/spritesheet.png")) {
        std::cerr << "Error loading sprite sheet texture!" << std::endl;
    }

    mIdleFrames = { "idle1.png", "idle2.png", "idle3.png", "idle4.png" };
    mRunFrames = { "run1.png", "run2.png", "run3.png", "run4.png", "run5.png", "run6.png" };
    mJumpFrames = { "jump1.png", "jump2.png", "jump3.png", "jump4.png" };


    mCurrentAnimation = "idle";
    mPreviousAnimation = mCurrentAnimation;
    loadSprite("idle1.png");
    mSprite.setPosition(50.0f, 450.0f);
}

void Player::handleInput() {
    mVelocity.x = 0.0f;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        mVelocity.x = -mSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        mVelocity.x = mSpeed;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && mSprite.getPosition().y >= mGroundLevel) {
        mVelocity.y = -500.0f;
        mJumpStartY = mSprite.getPosition().y;
    }
}

void Player::update(sf::Time dt) {
    mVelocity.y += mGravity * dt.asSeconds();

    mSprite.move(mVelocity * dt.asSeconds());

    if (mSprite.getPosition().y < mJumpStartY - mMaxJumpHeight) {
        mSprite.setPosition(mSprite.getPosition().x, mJumpStartY - mMaxJumpHeight);
        mVelocity.y = 0.0f;
    }

    if (mSprite.getPosition().y > mGroundLevel) {
        mSprite.setPosition(mSprite.getPosition().x, mGroundLevel);
        mVelocity.y = 0.0f;
    }

    if (mVelocity.x != 0.0f && mSprite.getPosition().y >= mGroundLevel) {
        mCurrentAnimation = "run";
    }
    else if (mSprite.getPosition().y < mGroundLevel) {
		mCurrentAnimation = "jump";
    }
    else {
        mCurrentAnimation = "idle";
    }

    updateAnimation(dt);
}

void Player::render(sf::RenderWindow& window) {
    window.draw(mSprite);
}

void Player::loadSprite(const std::string& spriteName) {
	std::ifstream file("assets/images/spritesheet.json");
    nlohmann::json json;
    file >> json;

    auto frame = json["frames"][spriteName]["frame"];
    int x = frame["x"];
    int y = frame["y"];
    int w = frame["w"];
    int h = frame["h"];

    mSprite.setTexture(mTexture);
    mSprite.setTextureRect(sf::IntRect(x, y, w, h));
}

void Player::updateAnimation(sf::Time dt) {
    mElapsedTime += dt;

    if (mCurrentAnimation != mPreviousAnimation) {
        mCurrentFrame = 0;
        mPreviousAnimation = mCurrentAnimation;
    }

    if (mElapsedTime >= mFrameTime) {
        mElapsedTime = sf::Time::Zero;

        if (mCurrentAnimation == "idle") {
            mCurrentFrame = (mCurrentFrame + 1) % mIdleFrames.size();
            loadSprite(mIdleFrames[mCurrentFrame]);
        }
        else if (mCurrentAnimation == "run") {
            mCurrentFrame = (mCurrentFrame + 1) % mRunFrames.size();
            loadSprite(mRunFrames[mCurrentFrame]);
		}
        else if (mCurrentAnimation == "jump") {
            mCurrentFrame = (mCurrentFrame + 1) % mJumpFrames.size();
            loadSprite(mJumpFrames[mCurrentFrame]);
        }
    }
}