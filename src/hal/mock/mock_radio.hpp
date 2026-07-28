#pragma once

#include "hal/interfaces/i_radio.hpp"
#include <iostream>
#include <cstring>
#include <iomanip>

class MockRadio : public IRadio {
public:
    bool isDataAvailable = false;
    uint8_t mockBuffer[32] = {0};
    size_t mockDataLen = 0;

    /// @brief Simulates incoming data availability.
    bool available() override {
        return isDataAvailable;
    }

    /// @brief Reads simulated data into the provided buffer.
    bool receive(uint8_t* buffer, size_t maxLen) override {
        if (!isDataAvailable) return false;

        size_t bytesToCopy = (maxLen < mockDataLen) ? maxLen : mockDataLen;
        std::memcpy(buffer, mockBuffer, bytesToCopy);
        
        isDataAvailable = false; // Packet consumed
        return true;
    }

    /// @brief Simulates packet transmission and logs output in hexadecimal format.
    bool send(const uint8_t* data, size_t len) override {
        std::cout << "[MOCK RADIO] Transmitting " << len << " bytes (HEX): ";
        for (size_t i = 0; i < len && i < 16; ++i) { // Show first 16 bytes to keep logs clean
            std::cout << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(data[i]) << " ";
        }
        if (len > 16) {
            std::cout << "...";
        }
        std::cout << std::dec << std::endl;
        return true;
    }

    /// @brief Helper method for tests on Mac: Simulates an incoming message.
    void simulateIncomingPacket(const char* message) {
        mockDataLen = std::strlen(message) + 1; // Includes null terminator
        std::memcpy(mockBuffer, message, mockDataLen);
        isDataAvailable = true;
    }
};