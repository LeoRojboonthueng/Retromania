#include "../../include/states/StateStack.hpp"

StateStack::StateStack(sf::RenderWindow& window)
    : mWindow(window) {
}

void StateStack::pushState(int stateID) {
    if (!mStack.empty()) {
        mStack.back()->onExit();
    }
    mPendingChanges.push_back({ Push, stateID });
}


void StateStack::popState() {
    if (!mStack.empty()) {
        mStack.back()->onExit();
    }
    mStack.pop_back();
    if (!mStack.empty()) {
        mStack.back()->onEnter();
    }
}

void StateStack::clearStates() {
    mPendingChanges.push_back({ Clear, 0 });
	mPendingChanges.push_back({ Push, 0 });
}


void StateStack::applyPendingChanges() {
    for (const auto& change : mPendingChanges) {
        switch (change.action) {
        case Push:
            if (mFactories.find(change.stateID) != mFactories.end()) {
                std::unique_ptr<State> newState = mFactories[change.stateID]();
                if (newState) {
                    mStack.push_back(std::move(newState));
                    mStack.back()->onEnter();
                }
                else {
                    std::cerr << "ERROR: StateStack.cpp - Something failed when trying to create the state, you passed in: " << change.stateID << std::endl;
                }
            }
            else {
                std::cerr << "ERROR: StateStack.cpp - That state aint a thing, you passed in: " << change.stateID << std::endl;
            }
            break;

        case Pop:
            if (!mStack.empty()) {
                mStack.pop_back();
                mStack.back()->onEnter();
            }
            else {
                std::cout << "WARN: StateStack.cpp - Tried to pop empty stack, what are you doing to do this?" << std::endl;
            }
            break;

        case Clear:
            mStack.clear();
            break;
        }
    }
    mPendingChanges.clear();
}

void StateStack::handleInput() {
    if (!mStack.empty()) {
        mStack.back()->handleInput(mWindow);
    }
}

void StateStack::update(sf::Time dt) {
    if (!mStack.empty()) {
        mStack.back()->update(dt);
    }
}


void StateStack::render() {
    if (!mStack.empty()) {
        mStack.back()->render(mWindow);
    }
    applyPendingChanges();
}