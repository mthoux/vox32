#pragma once

#include "hal/interfaces/i_output.hpp"
#include <iostream>

class MockOutput : public IOutput {
public:
    bool rxLedState = false;
    bool txLedState = false;

    /// @brief Simulates setting the RX LED state and logs status changes.
    /// @param active True to turn on the simulated LED, false to turn it off.
    void setRxLed(bool active) override {
        if (rxLedState != active) {
            rxLedState = active;
            std::cout << "[MOCK OUTPUT] RX LED (Blue) : " 
                      << (active ? "🟢 ON" : "🔴 OFF") << std::endl;
        }
    }

    /// @brief Simulates setting the TX LED state and logs status changes.
    /// @param active True to turn on the simulated LED, false to turn it off.
    void setTxLed(bool active) override {
        if (txLedState != active) {
            txLedState = active;
            std::cout << "[MOCK OUTPUT] TX LED (Green) : " 
                      << (active ? "🟢 ON" : "🔴 OFF") << std::endl;
        }
    }
};