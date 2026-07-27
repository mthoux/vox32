#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"

void StateTx::enter(Controller& controller) {
    // radio_set_mode_tx();
    // microphone_enable(true);
    // led_set_red();
    digitalWrite(PIN_GREEN_LED, HIGH);
}

void StateTx::update(Controller& controller, float dt) {

    if(digitalRead(PIN_BTN) == HIGH) {
        controller.changeState(StateIdle::getInstance());
        return;
    }

    RF24& radio = controller.getRadio();

    radio.stopListening();
    const char texte[] = "PING!";
    
    radio.write(&texte, sizeof(texte));
    Serial.println("📡 Message 'PING!' envoyé !");
    
    radio.startListening();
}

void StateTx::exit(Controller& controller) {
    // microphone_enable(false);
    // send_tail_tone(); // Petit bip de fin
    digitalWrite(PIN_GREEN_LED, LOW);
}