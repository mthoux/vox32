#include "controller.hpp"

void Controller::init(State& initialState) {
    currentState = &initialState;
    
    // Enter initial state
    currentState->enter(*this);
}

void Controller::update(float dt) {
    if (!currentState) return;

    // Update current state
    currentState->update(*this, dt);
}

void Controller::changeState(State& newState) {
    if (currentState) currentState->exit(*this);

    currentState = &newState;

    if (currentState) currentState->enter(*this);
}