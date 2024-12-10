#ifndef PLAYSTATE_HPP
#define PLAYSTATE_HPP

#include "../core/State.hpp"
#include "../entities/Player.hpp"
#include "../entities/Platform.hpp"
#include <SFML/Graphics.hpp>

class PlayState : public State {
public:
    explicit PlayState(StateStack& stack);

    void handleInput(sf::RenderWindow& window) override;
    void update(sf::Time dt) override;
    void render(sf::RenderWindow& window) override;

private:
    sf::Texture mBackgroundTexture;
    sf::Sprite mBackgroundSprite;

	std::vector<Platform> mPlatforms;

    Player mPlayer;
    float mPlayerSpeed = 200.0f;
};

#endif  // PLAYSTATE_HPP
