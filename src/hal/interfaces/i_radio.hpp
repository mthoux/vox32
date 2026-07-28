#pragma once

#include <cstddef>
#include <cstdint>

class IRadio {
public:
    virtual ~IRadio() = default;
    
    /// @brief Checks if at least one data packet is available in the buffer.
    /// @return true if data is waiting to be read, false otherwise.
    virtual bool available() = 0;

    /// @brief Reads received data and copies it into the provided buffer.
    /// @param buffer Pointer to the array that will receive the bytes.
    /// @param maxLen Maximum size to read (e.g., 32 bytes).
    /// @return true if the read operation succeeded, false otherwise.
    virtual bool receive(uint8_t* buffer, size_t maxLen) = 0;

    /// @brief Transmits a data packet over the radio network.
    /// @param data Pointer to the data to send.
    /// @param len Size of the data to send in bytes.
    /// @return true if transmission succeeded, false otherwise.
    virtual bool send(const uint8_t* data, size_t len) = 0;
};