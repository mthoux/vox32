#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"
#include <iostream>

void StateTx::enter(Controller& controller) {
    controller.getOutput().setTxLed(true);
    controller.getMicro().start();
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
    // send_tail_tone(); // Petit bip de fin
    controller.getMicro().stop();
    controller.getOutput().setTxLed(false);
}