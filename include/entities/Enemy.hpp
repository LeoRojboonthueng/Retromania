#ifndef ENEMY_HPP
#define ENEMY_HPP

#include <SFML/Graphics.hpp>
#include <vector>

class Enemy {
public:
    Enemy(float startX, float startY, float patrolDistance, float speed);
    void update(sf::Time dt, const sf::Vector2f& playerPosition);
    void render(sf::RenderWindow& window) const;
    sf::Sprite& getSprite();
    sf::Vector2f getPosition() const;

private:

    sf::Sprite mSprite;
    static sf::Texture mTexture;
    sf::Vector2f mStartPosition;
    float mPatrolDistance;
    float mSpeed;
    bool mMovingRight;
    float mDetectionRadius;
	float mJumpSpeed;
	float mGravity;
	bool mIsJumping;
	float mVerticalSpeed;

    void patrol(sf::Time dt);
    void chasePlayer(const sf::Vector2f& playerPosition, sf::Time dt);
};

#endif