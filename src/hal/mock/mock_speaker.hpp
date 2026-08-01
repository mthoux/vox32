#pragma once

#include "hal/interfaces/i_speaker.hpp"
#include <iostream>
#include <vector>
#include <cstdint>
#include <cstddef>

class MockSpeaker : public ISpeaker {
public:
    bool initialized = false;
    bool isMuted = false;
    bool busy = false;

    // Stocke les derniers échantillons envoyés pour inspection dans tes tests
    std::vector<int16_t> lastPlayedSamples;
    size_t totalSamplesPlayed = 0;

    /// @brief Simulates hardware initialization.
    bool init() override {
        initialized = true;
        std::cout << "[MOCK SPEAKER] Initialized successfully." << std::endl;
        return true;
    }

    /// @brief Simulates playing audio samples and logs output.
    bool play(const int16_t* samples, size_t count) override {
        if (!initialized) {
            std::cout << "[MOCK SPEAKER] Error: Speaker not initialized!" << std::endl;
            return false;
        }

        if (isMuted) {
            std::cout << "[MOCK SPEAKER] Warning: Playing audio while muted." << std::endl;
        }

        lastPlayedSamples.assign(samples, samples + count);
        totalSamplesPlayed += count;
        busy = true;

        std::cout << "[MOCK SPEAKER] Playing " << count << " samples (First 8 PCM values): ";
        for (size_t i = 0; i < count && i < 8; ++i) {
            std::cout << samples[i] << " ";
        }
        if (count > 8) {
            std::cout << "...";
        }
        std::cout << std::endl;

        return true;
    }

    /// @brief Simulates stopping audio playback.
    void stop() override {
        busy = false;
        std::cout << "[MOCK SPEAKER] Playback stopped." << std::endl;
    }

    /// @brief Simulates setting mute state (controlling MAX98357A SD pin).
    void setMute(bool mute) override {
        isMuted = mute;
        std::cout << "[MOCK SPEAKER] Mute state set to: " << (mute ? "ENABLED" : "DISABLED") << std::endl;
    }

    /// @brief Checks if speaker is currently simulated as busy.
    bool isBusy() override {
        return busy;
    }

    /// @brief Helper for unit tests: Resets state and recorded buffers.
    void resetMock() {
        initialized = false;
        isMuted = false;
        busy = false;
        totalSamplesPlayed = 0;
        lastPlayedSamples.clear();
    }
};