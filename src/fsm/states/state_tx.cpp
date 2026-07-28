#include "state_tx.hpp"
#include "state_idle.hpp"
#include "../controller.hpp"
#include <iostream>
#include <vector>

void StateTx::enter(Controller& controller) {
    controller.getOutput().setTxLed(true);
    controller.getMicro().start();
}

void StateTx::update(Controller& controller, float dt) {

    if(!controller.getInput().isButtonPressed()) {
        controller.changeState(StateIdle::getInstance());
        return;
    }

    // Read audio samples from the microphone
    constexpr std::size_t BUFFER_SIZE = 512;
    std::vector<uint8_t> buffer(BUFFER_SIZE);

    // Read actual recorded data from the microphone
    std::size_t bytesRead = controller.getMicro().read(buffer.data(), BUFFER_SIZE);

    if (bytesRead > 0) {
        // Compress data via ADPCM
        // std::vector<uint8_t> buffer = compressAudio(buffer, bytesRead);

        // Send compressed data via the radio module
        bool sendSuccess = controller.getRadio().send(buffer.data(), buffer.size());

        if (sendSuccess) {
            std::cout << "📡 " << buffer.size() << " bytes of audio transmitted!" << std::endl;
        } else {
            std::cerr << "⚠️ Radio transmission failed." << std::endl;
        }
    }
}

void StateTx::exit(Controller& controller) {
    // send_tail_tone(); // Short end beep
    controller.getMicro().stop();
    controller.getOutput().setTxLed(false);
}