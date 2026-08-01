#pragma once

#include <cstddef>
#include <cstdint>

class ISpeaker {
public:
    virtual ~ISpeaker() = default;

    /// @brief Initializes the speaker hardware (e.g. I2S peripheral and control pins).
    /// @return true if initialization succeeded, false otherwise.
    virtual bool init() = 0;

    /// @brief Plays a buffer of PCM audio samples.
    /// @param samples Pointer to the 16-bit PCM audio samples buffer.
    /// @param count Number of samples to play (length of array).
    /// @return true if audio data was successfully queued/written, false on error.
    virtual bool play(const int16_t* samples, size_t count) = 0;

    /// @brief Stops audio playback immediately and clears internal audio buffers.
    virtual void stop() = 0;

    /// @brief Enables or disables the amplifier (SD pin on MAX98357A).
    /// @param mute true to mute/power-down the amplifier, false to enable it.
    virtual void setMute(bool mute) = 0;

    /// @brief Checks if audio is currently being transmitted to the speaker.
    /// @return true if speaker is busy playing audio, false otherwise.
    virtual bool isBusy() = 0;
};