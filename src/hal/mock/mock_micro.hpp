#pragma once

#include "hal/interfaces/i_micro.hpp"
#include <iostream>

class MockMicro : public IMicro {
private:
    bool isRunning = false;
    uint8_t counter = 0;

public:
    bool start() override {
        isRunning = true;
        std::cout << "[Mock] Microphone started" << std::endl;
        return true;
    }
    
    void stop() override {
        isRunning = false;
        std::cout << "[Mock] Microphone stopped" << std::endl;
    }

    bool available() override {
        return isRunning;
    }

    size_t read(uint8_t* buffer, size_t maxLen) override {
        if (!isRunning || maxLen == 0) return 0;

        // Fill buffer with fake audio data (e.g., a ramp)
        size_t bytesToRead = (maxLen < 32) ? maxLen : 32; // simulate chunks of 32 bytes
        for (size_t i = 0; i < bytesToRead; i++) {
            buffer[i] = counter++;
        }
        
        return bytesToRead;
    }
};