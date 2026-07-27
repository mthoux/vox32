#include "controller.hpp"
#include <Arduino.h>

void Controller::init(State& initialState) {
    currentState = &initialState;
    lastTimeMs = millis();
    
    // Enter initial state
    currentState->enter(*this);
}

void Controller::update() {
    if (!currentState) return;

    // Compute dt in seconds
    uint32_t now = millis();
    float dt = (now - lastTimeMs) / 1000.0f;
    lastTimeMs = now;

    // Update current state
    currentState->update(*this, dt);
}

void Controller::changeState(State& newState) {
    if (currentState) currentState->exit(*this);

    currentState = &newState;

    if (currentState) currentState->enter(*this);
}