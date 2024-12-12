#include "../../include/entities/Enemy.hpp"
#include <cmath>

sf::Texture Enemy::mTexture;

Enemy::Enemy(float startX, float startY, float patrolDistance, float speed)
    : mStartPosition(startX, startY), mPatrolDistance(patrolDistance), mSpeed(speed), mMovingRight(true), mDetectionRadius(200.0f), mJumpSpeed(500.0f), mGravity(1500.0f), mIsJumping(false), mVerticalSpeed(0.0f) {
    if (mTexture.getSize().x == 0) {
        if (!mTexture.loadFromFile("assets/images/enemy.png")) {
            throw std::runtime_error("Error loading enemy texture!");
        }
    }
    mSprite.setTexture(mTexture);
    mSprite.setPosition(mStartPosition);
}

void Enemy::update(sf::Time dt, const sf::Vector2f& playerPosition) {
    float distanceToPlayer = std::sqrt(std::pow(playerPosition.x - mSprite.getPosition().x, 2) + std::pow(playerPosition.y - mSprite.getPosition().y, 2));
    if (distanceToPlayer <= mDetectionRadius) {
        chasePlayer(playerPosition, dt);
    }
    else {
        patrol(dt);
    }

    if (mIsJumping) {
        mVerticalSpeed += mGravity * dt.asSeconds();
        mSprite.move(0, mVerticalSpeed * dt.asSeconds());
        if (mSprite.getPosition().y >= mStartPosition.y) {
            mSprite.setPosition(mSprite.getPosition().x, mStartPosition.y);
            mIsJumping = false;
            mVerticalSpeed = 0.0f;
        }
    }
}

void Enemy::render(sf::RenderWindow& window) const {
    window.draw(mSprite);
}

sf::Vector2f Enemy::getPosition() const {
    return mSprite.getPosition();
}

sf::Sprite& Enemy::getSprite() {
    return mSprite;
}

void Enemy::patrol(sf::Time dt) {
    if (mMovingRight) {
        mSprite.move(mSpeed * dt.asSeconds(), 0);
        if (mSprite.getPosition().x > mStartPosition.x + mPatrolDistance) {
            mMovingRight = false;
        }
    }
    else {
        mSprite.move(-mSpeed * dt.asSeconds(), 0);
        if (mSprite.getPosition().x < mStartPosition.x - mPatrolDistance) {
            mMovingRight = true;
        }
    }
}

void Enemy::chasePlayer(const sf::Vector2f& playerPosition, sf::Time dt) {
    if (playerPosition.x > mSprite.getPosition().x) {
        mSprite.move(mSpeed * dt.asSeconds(), 0);
    }
    else {
        mSprite.move(-mSpeed * dt.asSeconds(), 0);
    }

    float enemyBottom = mSprite.getPosition().y + mSprite.getGlobalBounds().height;
    if (playerPosition.y < enemyBottom && !mIsJumping) {
        mIsJumping = true;
        mVerticalSpeed = -mJumpSpeed;
    }
}
