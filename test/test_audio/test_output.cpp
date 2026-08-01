#include <Arduino.h>
#include <WiFi.h>
#include "Audio.h"

// Configuration des pins I2S pour le MAX98357A
constexpr uint8_t PIN_LRC  = 26;
constexpr uint8_t PIN_BCLK = 27;
constexpr uint8_t PIN_DIN  = 22;

const char* ssid     = "Loutrys";
const char* password = "Flipsymiaoucr0quette";

Audio audio;

void setup() {
    Serial.begin(115200);

    // Connexion Wi-Fi
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nWi-Fi connecté !");

    // Configuration des broches pour l'ampli MAX98357A
    audio.setPinout(PIN_BCLK, PIN_LRC, PIN_DIN);
    
    // Réglage du volume (de 0 à 21)
    audio.setVolume(10);

    // Lancement d'une radio web en streaming (France Info par exemple)
    audio.connecttohost("http://icecast.radiofrance.fr/franceinfo-midfi.mp3");
}

void loop() {
    // La méthode loop doit être appelée en continu pour alimenter le flux audio
    audio.loop();
}