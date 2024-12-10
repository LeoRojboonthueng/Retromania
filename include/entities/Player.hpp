#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <SFML/Graphics.hpp>
#include "Platform.hpp"

class Player {
public:
    Player();

    void handleInput();
    void update(sf::Time dt, const std::vector<Platform>& platforms);
    void render(sf::RenderWindow& window);
    sf::Sprite& getSprite();

private:
    sf::Sprite mSprite;
    sf::Texture mTexture;
    sf::Vector2f mVelocity;
    float mSpeed;

    std::vector<std::string> mIdleFrames;
    std::vector<std::string> mRunFrames;
	std::vector<std::string> mJumpFrames;
    std::string mCurrentAnimation;
    std::string mPreviousAnimation;
    size_t mCurrentFrame;
    sf::Time mFrameTime;
    sf::Time mElapsedTime;

    float mGravity;
    float mGroundLevel;
    float mJumpStartY;
    float mMaxJumpHeight;

    void loadSprite(const std::string& spriteName);
    void updateAnimation(sf::Time dt);
    void checkCollisions(const std::vector<Platform>& platforms);
};

#endif
