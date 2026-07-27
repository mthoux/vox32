#pragma once

#include "i_input.hpp"
#include <Arduino.h>

class Esp32Input : public IInput {
private:
    uint8_t pin;

public:
    explicit Esp32Input(uint8_t buttonPin) : pin(buttonPin) {}

    void init() {
        pinMode(pin, INPUT_PULLUP);
    }

    bool isButtonPressed() override {
        return digitalRead(pin) == LOW;
    }
};