#pragma once

#include "i_input.hpp"

class MockInput : public IInput {
public:
    bool buttonState = false;

    bool isButtonPressed() override {
        return buttonState;
    }
};