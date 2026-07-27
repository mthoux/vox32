#include "state_rx.hpp"
#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"

void StateRx::enter(Controller& controller) {
    controller.getOutput().setRxLed(true);
}

void StateRx::update(Controller& controller, float dt) {

    if(controller.getInput().isButtonPressed()) {
        controller.changeState(StateTx::getInstance());
        return;
    }

    IRadio& radio = controller.getRadio();

    if (radio.available()) {

        uint8_t buffer[32] = {0};
        radio.receive(buffer, sizeof(buffer));
      
        // Serial.print("📩 Message reçu: ");
        // Serial.println(texteRecu);

        } else {
            controller.changeState(StateIdle::getInstance());
            return;
        }
}

void StateRx::exit(Controller& controller) {
    controller.getOutput().setRxLed(false);
}