#pragma once

#include "i_radio.hpp"
#include <RF24.h>

class Esp32Radio : public IRadio {
private:
    RF24& rf24;

public:
    /// @brief Constructor wrapping the physical RF24 hardware instance.
    /// @param radioHardware Reference to the configured RF24 object.
    explicit Esp32Radio(RF24& radioHardware) : rf24(radioHardware) {}

    /// @brief Checks if at least one data packet is available in the NRF24 FIFO.
    /// @return true if data is available, false otherwise.
    bool available() override {
        return rf24.available();
    }

    /// @brief Reads received bytes from the NRF24 FIFO into the target buffer.
    /// @param buffer Pointer to the destination array.
    /// @param maxLen Maximum number of bytes to read.
    /// @return Always true upon reading.
    bool receive(uint8_t* buffer, size_t maxLen) override {
        rf24.read(buffer, maxLen);
        return true;
    }

    /// @brief Transmits a data packet by temporarily stopping RX, sending, and resuming RX.
    /// @param data Pointer to the payload bytes to transmit.
    /// @param len Size of the payload in bytes.
    /// @return true if transmission succeeded, false otherwise.
    bool send(const uint8_t* data, size_t len) override {
        rf24.stopListening();
        bool success = rf24.write(data, len);
        rf24.startListening();
        return success;
    }
};