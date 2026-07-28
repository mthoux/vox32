#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>
#include <cmath>
#include "adpcm.h"

// En-tête WAV standard (44 octets)
struct WavHeader {
    char riff[4] = {'R', 'I', 'F', 'F'};
    uint32_t chunkSize;
    char wave[4] = {'W', 'A', 'V', 'E'};
    char fmt[4] = {'f', 'm', 't', ' '};
    uint32_t fmtSize = 16;
    uint16_t audioFormat = 1; // PCM
    uint16_t numChannels = 1; // Mono
    uint32_t sampleRate = 16000;
    uint32_t byteRate = 32000; // 16000 * 1 * 2
    uint16_t blockAlign = 2;   // 1 * 2
    uint16_t bitsPerSample = 16;
    char data[4] = {'d', 'a', 't', 'a'};
    uint32_t dataSize;
};

int main() {
    std::cout << "=== TEST ENCODEUR / DÉCODEUR ADPCM ===" << std::endl;

    // 1. Ouverture du fichier source
    std::ifstream inputFile("test/data/chirp_16k.wav", std::ios::binary);
    if (!inputFile.is_open()) {
        std::cerr << "Erreur: Impossible d'ouvrir test_conde.wav !" << std::endl;
        std::cerr << "Assure-toi que le fichier est a la racine de l'execution." << std::endl;
        return 1;
    }

    // Sauter l'en-tête de 44 octets pour lire le PCM brut
    inputFile.seekg(44, std::ios::beg);

    // 2. Ouverture du fichier de sortie décodé
    std::ofstream outputFile("test/data/resultat_decode.wav", std::ios::binary);
    if (!outputFile.is_open()) {
        std::cerr << "Erreur: Impossible de créer resultat_decode.wav !" << std::endl;
        return 1;
    }

    // Écrire un header temporaire (on mettra à jour la taille à la fin)
    WavHeader outHeader;
    outputFile.write(reinterpret_cast<char*>(&outHeader), sizeof(WavHeader));

    // Initialisation des états ADPCM (un pour l'émetteur, un pour le récepteur)
    AdpcmState encoderState = {0, 0};
    AdpcmState decoderState = {0, 0};

    // Buffers de travail
    int16_t pcmInput[256];        // 512 octets lus depuis le WAV
    uint8_t adpcmBuffer[128];     // 128 octets après compression (512 / 4)
    int16_t pcmOutput[256];       // 512 octets après décompression

    int totalBlocks = 0;
    uint32_t totalBytesWritten = 0;

    // 3. Boucle de traitement par blocs de 512 octets
    while (inputFile.read(reinterpret_cast<char*>(pcmInput), sizeof(pcmInput))) {
        totalBlocks++;

        // A. Compression (ESP32 Émetteur)
        adpcm_encode(pcmInput, adpcmBuffer, 256, &encoderState);

        // --- SIMULATION RADIO (nRF24L01) ---
        // Ici, adpcmBuffer (128 octets) serait découpé en 4 paquets de 32 octets :
        // Paquet 1: adpcmBuffer + 0
        // Paquet 2: adpcmBuffer + 32
        // Paquet 3: adpcmBuffer + 64
        // Paquet 4: adpcmBuffer + 96
        // ------------------------------------

        // B. Décompression (ESP32 Récepteur)
        adpcm_decode(adpcmBuffer, pcmOutput, 256, &decoderState);

        // C. Écriture du son décompressé dans le fichier final
        outputFile.write(reinterpret_cast<char*>(pcmOutput), sizeof(pcmOutput));
        totalBytesWritten += sizeof(pcmOutput);
    }

    // 4. Mettre à jour l'en-tête WAV avec la taille réelle du fichier généré
    outHeader.dataSize = totalBytesWritten;
    outHeader.chunkSize = totalBytesWritten + 36;
    outputFile.seekp(0, std::ios::beg);
    outputFile.write(reinterpret_cast<char*>(&outHeader), sizeof(WavHeader));

    inputFile.close();
    outputFile.close();

    std::cout << " Done !" << std::endl;
    std::cout << "Blocs traites : " << totalBlocks << std::endl;
    std::cout << "Taille audio generee : " << totalBytesWritten << " octets" << std::endl;
    std::cout << "\nPour ecouter le resultat sur Mac, tape dans le terminal :" << std::endl;
    std::cout << "afplay resultat_decode.wav" << std::endl;

    return 0;
}