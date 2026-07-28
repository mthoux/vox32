#pragma once

#include "hal/interfaces/i_output.hpp"
#include <Arduino.h>
#include <cstdint>

class Esp32Output : public IOutput {
private:
    uint8_t rxLedPin;
    uint8_t txLedPin;

public:
    /// @brief Constructor configuring GPIO pins for the status LEDs.
    /// @param rxPin Pin number for the RX LED (Blue).
    /// @param txPin Pin number for the TX LED (Green).
    Esp32Output(uint8_t rxPin, uint8_t txPin) 
        : rxLedPin(rxPin), txLedPin(txPin) {}

    /// @brief Initializes GPIO pins as outputs and turns off both LEDs.
    void init() {
        pinMode(rxLedPin, OUTPUT);
        pinMode(txLedPin, OUTPUT);
        
        setRxLed(false);
        setTxLed(false);
    }

    void setRxLed(bool active) override {
        digitalWrite(rxLedPin, active ? HIGH : LOW);
    }

    void setTxLed(bool active) override {
        digitalWrite(txLedPin, active ? HIGH : LOW);
    }
};