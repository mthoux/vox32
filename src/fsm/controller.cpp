#include "controller.hpp"
#include <iostream>

void Controller::init(State& initialState) {
    currentState = &initialState;
    
    std::cout << "[CONTROLLER] Initial state: " << currentState->getName() << std::endl;
    currentState->enter(*this);
}

void Controller::update(float dt) {
    if (!currentState) return;

    time_elapsed += dt;

    std::cout << "[CONTROLLER] Update at time: " << time_elapsed << "s" << std::endl;

    currentState->update(*this, dt);
}

void Controller::changeState(State& newState) {
    if (currentState) currentState->exit(*this);

    currentState = &newState;

    std::cout << "[CONTROLLER] Switched to state: " << currentState->getName() << std::endl;

    if (currentState) currentState->enter(*this);
}