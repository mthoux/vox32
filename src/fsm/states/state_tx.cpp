#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"
#include <iostream>

void StateTx::enter(Controller& controller) {
    // radio_set_mode_tx();
    // microphone_enable(true);
    // led_set_red();
    controller.getOutput().setTxLed(true);
}

void StateTx::update(Controller& controller, float dt) {

    if(!controller.getInput().isButtonPressed()) {
        controller.changeState(StateIdle::getInstance());
        return;
    }

    const uint8_t texte[] = "PING!";
    
    if (controller.getRadio().send(texte, sizeof(texte))) {
        std::cout << "📡 Message 'PING!' envoyé !" << std::endl;
    }
}

void StateTx::exit(Controller& controller) {
    // microphone_enable(false);
    // send_tail_tone(); // Petit bip de fin
    controller.getOutput().setTxLed(false);
}