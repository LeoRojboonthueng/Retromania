#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "../core/State.hpp"
#include "../entities/Player.hpp"
#include "../entities/Enemy.hpp"
#include "../entities/Platform.hpp"
#include "../entities/Level.hpp"
#include <SFML/Graphics.hpp>

class PlayState : public State {
public:
    explicit PlayState(StateStack& stack, sf::RenderWindow& window);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;
    void onEnter() override;
    void onExit() override;

private:
    sf::View mView;

    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;

	std::vector<Platform> mPlatforms;

    Player mPlayer;
    std::vector<Enemy> mEnemies;
    
    sf::Vector2f mSavedPlayerPosition;
    sf::View mSavedView;
    bool mFirstLoad;
	bool mPaused;

    sf::RectangleShape mEndBlock;
    int mCurrentLevel;
	std::vector<Level> mLevels;
    void loadLevel(int levelIndex);
    void checkEndBlockCollision();
};

#endif  // PLAYSTATE_HPP
