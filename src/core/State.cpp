#include "../../include/core/State.hpp"
#include "../../include/states/StateStack.hpp"

State::State(StateStack& stack, sf::RenderWindow& window)
    : mStack(stack), mWindow(window) {
}
