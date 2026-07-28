#pragma once 

#include <cstdint>
#include <cstddef>

// État de l'encodeur / décodeur ADPCM
struct AdpcmState {
    int16_t valprev; // Dernière valeur d'échantillon prédite
    int8_t index;    // Index actuel dans la table de pas
};

// Prototypes des fonctions
void adpcm_encode(const int16_t* pcm_in, uint8_t* adpcm_out, size_t num_samples, AdpcmState* state);
void adpcm_decode(const uint8_t* adpcm_in, int16_t* pcm_out, size_t num_samples, AdpcmState* state);
