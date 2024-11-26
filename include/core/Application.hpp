#ifndef APPLICATION_HPP
#define APPLICATION_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <memory>
#include "../states/StateStack.hpp"

class Application {
public:
    Application();
    void run();

private:
    void processEvents();
    void update(sf::Time dt);
    void render();

    static constexpr unsigned int WindowWidth = 800;
    static constexpr unsigned int WindowHeight = 600;
    static constexpr char WindowTitle[] = "Retromania";

    sf::RenderWindow mWindow;
    sf::Clock mClock;
    sf::Time mDeltaTime;

	StateStack mStateStack;
};

#endif
