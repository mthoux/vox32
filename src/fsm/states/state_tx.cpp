#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"
#include "pins.h"
#include <Arduino.h>

void StateTx::enter(Controller& controller) {
    // radio_set_mode_tx();
    // microphone_enable(true);
    // led_set_red();
}

void StateTx::update(Controller& controller, float dt) {
    // Si le bouton est relâché -> Retour en Idle
    // if (read_pin(PIN_PTT) == HIGH) { 
    //     controller.changeState(StateIdle::getInstance());
    //     return;
    // }
}

void StateTx::exit(Controller& controller) {
    // microphone_enable(false);
    // send_tail_tone(); // Petit bip de fin
}