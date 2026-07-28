#pragma once

class IOutput {
public:
    virtual ~IOutput() = default;

    /// @brief Control the reception LED (Blue)
    virtual void setRxLed(bool active) = 0;

    /// @brief Control the transmission LED (Green)
    virtual void setTxLed(bool active) = 0;
};