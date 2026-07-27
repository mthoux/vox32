#include "StateTx.hpp"
#include "StateIdle.hpp"         // Pour pouvoir retourner en IDLE
#include "RadioController.hpp"
#include "hardware.h"

void StateTx::enter(RadioController& controller) {
    radio_set_mode_tx();
    microphone_enable(true);
    led_set_red();
}

void StateTx::update(RadioController& controller, float dt) {
    // Si le bouton est relâché -> Retour en Idle
    if (read_pin(PIN_PTT) == HIGH) { 
        controller.changeState(StateIdle::getInstance());
        return;
    }
}

void StateTx::exit(RadioController& controller) {
    microphone_enable(false);
    send_tail_tone(); // Petit bip de fin
}