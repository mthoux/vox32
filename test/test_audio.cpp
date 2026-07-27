#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

// Si tu as déjà ton fichier ADPCM
#include "adpcm.h" 

int main() {
    // 1. Ouvrir le fichier WAV
    std::ifstream wavFile("test_conde.wav", std::ios::binary);
    if (!wavFile.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir le fichier WAV !" << std::endl;
        return 1;
    }

    // Sauter les 44 octets du Header WAV pour n'avoir QUE l'audio brut
    wavFile.seekg(44, std::ios::beg);

    // Buffer de lecture (ex: 256 échantillons de 16 bits = 512 octets)
    int16_t pcmBuffer[256]; 
    uint8_t compressedBuffer[128]; // ADPCM compresse par 4 (512 / 4 = 128 octets)

    std::cout << "--- DÉBUT DE LA SIMULATION TRANSMISSION ---" << std::endl;

    while (wavFile.read(reinterpret_cast<char*>(pcmBuffer), sizeof(pcmBuffer))) {
        
        // ----------------------------------------------------
        // ÉTAPE A : Calcul de l'amplitude (VOX)
        // ----------------------------------------------------
        int16_t maxAmplitude = 0;
        for (int i = 0; i < 256; i++) {
            if (std::abs(pcmBuffer[i]) > maxAmplitude) {
                maxAmplitude = std::abs(pcmBuffer[i]);
            }
        }

        // Si le son est trop faible (silence), on zap
        if (maxAmplitude < 1000) { 
            std::cout << "[VOX] Silence détecté (Amplitude: " << maxAmplitude << ") -> Paquet ignoré" << std::endl;
            continue; 
        }

        // ----------------------------------------------------
        // ÉTAPE B : Compression ADPCM
        // ----------------------------------------------------
        // adpcm_encode(pcmBuffer, compressedBuffer, 256);
        std::cout << "[CODEC] Bloc compressé de 512 B vers 128 B (Max Amp: " << maxAmplitude << ")" << std::endl;

        // ----------------------------------------------------
        // ÉTAPE C : Découpage pour le nRF24L01 (tranches de 32 octets)
        // ----------------------------------------------------
        int totalBytes = 128;
        int chunkSize = 32;

        for (int offset = 0; offset < totalBytes; offset += chunkSize) {
            // Simulation de l'envoi radio
            uint8_t* radioPacket = compressedBuffer + offset;
            
            std::cout << "   ---> [RADIO MOCK] Envoi paquet de 32 octets (Offset " << offset << ")" << std::endl;
        }
    }

    std::cout << "--- FIN DE LA SIMULATION ---" << std::endl;
    return 0;
}