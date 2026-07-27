#include "state_rx.hpp"
#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"

void StateIdle::enter(Controller& controller) {}

void StateIdle::update(Controller& controller, float dt) {

    if(digitalRead(PIN_BTN) == LOW) {
        controller.changeState(StateTx::getInstance());
        return;
    }

    if (controller.getRadio().available()) {
        controller.changeState(StateRx::getInstance());
        return;
    }
}

void StateIdle::exit(Controller& controller) {}