#pragma once

class IOutput {
public:
    virtual ~IOutput() = default;

    /// @brief Contrôle de la LED de réception (Bleue)
    virtual void setRxLed(bool active) = 0;

    /// @brief Contrôle de la LED d'émission (Verte)
    virtual void setTxLed(bool active) = 0;
};