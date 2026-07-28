#pragma once

#include <cstddef>
#include <cstdint>

class IMicro {
public:
    virtual ~IMicro() = default;

    /// @brief Starts the microphone audio capture (e.g., PTT pressed).
    /// @return true if successfully started, false otherwise.
    virtual bool start() = 0;

    /// @brief Stops the microphone audio capture (e.g., PTT released).
    virtual void stop() = 0;

    /// @brief Checks if audio data is available to be read from the microphone.
    /// @return true if audio samples are ready, false otherwise.
    virtual bool available() = 0;

    /// @brief Reads captured audio samples into the provided buffer.
    /// @param buffer Pointer to the buffer that will receive the audio data (e.g., PCM samples).
    /// @param maxLen Maximum size to read in bytes.
    /// @return Number of bytes actually read, or 0 if no data was read.
    virtual size_t read(uint8_t* buffer, size_t maxLen) = 0;
};