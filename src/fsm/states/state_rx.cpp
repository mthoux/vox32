#include "state_rx.hpp"
#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"

void StateRx::enter(Controller& controller) {
}

void StateRx::update(Controller& controller, float dt) {

    if(digitalRead(PIN_BTN) == LOW) {
        controller.changeState(StateTx::getInstance());
        return;
    }

    RF24& radio = controller.getRadio();

    if (radio.available()) {
      digitalWrite(PIN_BLUE_LED, HIGH);

      char texteRecu[32] = "";
      radio.read(&texteRecu, sizeof(texteRecu));
      
      Serial.print("📩 Message reçu: ");
      Serial.println(texteRecu);

      digitalWrite(PIN_BLUE_LED, LOW);
    } else {
        controller.changeState(StateIdle::getInstance());
        return;
    }
}

void StateRx::exit(Controller& controller) {
}