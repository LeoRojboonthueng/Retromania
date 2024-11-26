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

    explicit StateStack();

    template <typename T>
    void registerState(int stateID);

    void pushState(int stateID);
    void popState();
    void clearStates();
    void handleInput(sf::RenderWindow& window);
    void update(sf::Time dt);
    void render(sf::RenderWindow& window);

private:
    struct PendingChange {
        Action action;
        int stateID;
    };

    void applyPendingChanges();

    std::vector<std::unique_ptr<State>> mStack;
    std::vector<PendingChange> mPendingChanges;
    std::map<int, std::function<std::unique_ptr<State>()>> mFactories;
};

template <typename T>
void StateStack::registerState(int stateID) {
    mFactories[stateID] = [this]() { return std::make_unique<T>(*this); };
    std::cout << "Registered state with ID: " << stateID << std::endl;
}

#endif
