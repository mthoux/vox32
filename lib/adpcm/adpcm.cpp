#include "adpcm.h"

// Tables de constantes officielles de la norme IMA ADPCM
static const int indexTable[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};

static const int stepsizeTable[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
    2272, 2499, 2749, 3024, 3326, 3659, 4025, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};

void adpcm_encode(const int16_t* pcm_in, uint8_t* adpcm_out, size_t num_samples, AdpcmState* state) {
    int val = state->valprev;
    int index = state->index;
    int step = stepsizeTable[index];

    for (size_t i = 0; i < num_samples; i++) {
        int sample = pcm_in[i];
        int diff = sample - val;
        int sign = (diff < 0) ? 8 : 0;
        if (sign) diff = -diff;

        int delta = 0;
        if (diff >= step) { delta |= 4; diff -= step; }
        if (diff >= step >> 1) { delta |= 2; diff -= step >> 1; }
        if (diff >= step >> 2) { delta |= 1; }

        // Mettre à jour la prédiction
        int vpdiff = (step >> 3);
        if (delta & 4) vpdiff += step;
        if (delta & 2) vpdiff += (step >> 1);
        if (delta & 1) vpdiff += (step >> 2);

        if (sign) val -= vpdiff;
        else val += vpdiff;

        // Saturation 16 bits
        if (val > 32767) val = 32767;
        else if (val < -32768) val = -32768;

        // Mise à jour de l'index
        index += indexTable[delta];
        if (index < 0) index = 0;
        if (index > 88) index = 88;
        step = stepsizeTable[index];

        delta |= sign;

        // On empaquète 2 nibbles (4-bit) dans 1 octet (8-bit)
        if (i % 2 == 0) {
            adpcm_out[i / 2] = delta & 0x0F;
        } else {
            adpcm_out[i / 2] |= (delta << 4);
        }
    }

    state->valprev = (int16_t)val;
    state->index = (int8_t)index;
}

void adpcm_decode(const uint8_t* adpcm_in, int16_t* pcm_out, size_t num_samples, AdpcmState* state) {
    int val = state->valprev;
    int index = state->index;
    int step = stepsizeTable[index];

    for (size_t i = 0; i < num_samples; i++) {
        uint8_t delta;
        if (i % 2 == 0) {
            delta = adpcm_in[i / 2] & 0x0F;
        } else {
            delta = (adpcm_in[i / 2] >> 4) & 0x0F;
        }

        int sign = delta & 8;
        int delta_val = delta & 7;

        int vpdiff = (step >> 3);
        if (delta_val & 4) vpdiff += step;
        if (delta_val & 2) vpdiff += (step >> 1);
        if (delta_val & 1) vpdiff += (step >> 2);

        if (sign) val -= vpdiff;
        else val += vpdiff;

        if (val > 32767) val = 32767;
        else if (val < -32768) val = -32768;

        index += indexTable[delta_val | sign];
        if (index < 0) index = 0;
        if (index > 88) index = 88;
        step = stepsizeTable[index];

        pcm_out[i] = (int16_t)val;
    }

    state->valprev = (int16_t)val;
    state->index = (int8_t)index;
}