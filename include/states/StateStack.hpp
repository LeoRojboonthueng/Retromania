#ifndef STATESTACK_HPP
#define STATESTACK_HPP

#include "../core/State.hpp"
#include <memory>
#include <vector>
#include <functional>
#include <map>
#include <iostream>

class StateStack {
public:
    enum Action {
        Push,
        Pop,
        Clear
    };

    explicit StateStack(sf::RenderWindow& window);

    template <typename T>
    void registerState(int stateID);

    void pushState(int stateID);
    void popState();
    void clearStates();
    void handleInput();
    void update(sf::Time dt);
    void render();

private:
    struct PendingChange {
        Action action;
        int stateID;
    };

    void applyPendingChanges();

    std::vector<std::unique_ptr<State>> mStack;
    std::vector<PendingChange> mPendingChanges;
    std::map<int, std::function<std::unique_ptr<State>()>> mFactories;
    sf::RenderWindow& mWindow;
};

template <typename T>
void StateStack::registerState(int stateID) {
    mFactories[stateID] = [this]() { return std::make_unique<T>(*this, mWindow); };
    std::cout << "Registered state with ID: " << stateID << std::endl;
}

#endif
