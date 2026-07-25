#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

#define PIN_CE  4
#define PIN_CSN 5
#define PIN_PTT 16 

RF24 radio(PIN_CE, PIN_CSN);
bool nrfInitialise = false;
const byte adresse[6] = "00001";

unsigned long compteurLoop = 0; // Pour compter les tours de boucle

void setup() {
  Serial.begin(115200);
  delay(2000); 
  
  Serial.println("\n==========================================");
  Serial.println("🔄 DÉMARRAGE MODE AFFICHAGE CONTINU");
  Serial.println("==========================================");

  pinMode(PIN_PTT, INPUT_PULLUP);

  SPI.begin(18, 19, 23, PIN_CSN);

  if (!radio.begin()) {
    Serial.println("🔴 NRF24 : NON DÉTECTÉ au démarrage");
    nrfInitialise = false;
  } else {
    Serial.println("🟢 NRF24 : DÉTECTÉ au démarrage !");
    nrfInitialise = true;
    
    radio.setPALevel(RF24_PA_MIN);
    radio.setAutoAck(false);       
    radio.setRetries(0, 0);        
    
    radio.openWritingPipe(adresse);
    radio.openReadingPipe(1, adresse);
    radio.startListening();
  }

  Serial.println("\n--- DÉBUT DE LA BOUCLE PERMANENTE ---");
}

void loop() {
  compteurLoop++;
  int etatBouton = digitalRead(PIN_PTT);

  // 1. AFFICHAGE EN BOUCLE DU STATUT (Toutes les 500 ms)
  Serial.print("[Tour ");
  Serial.print(compteurLoop);
  Serial.print("] Pin 16 = ");
  Serial.print(etatBouton);
  
  if (etatBouton == LOW) {
    Serial.print(" (LOW -> APPUI DÉTECTÉ !)");
  } else {
    Serial.print(" (HIGH -> Relâché)");
  }

  // 2. ACTION SI APPUYÉ
  if (etatBouton == LOW) {
    Serial.print(" ➔ 🎙️ MODE ÉMISSION... ");

    if (nrfInitialise) {
      radio.stopListening();
      const char texte[] = "PING!";
      
      // Envoi
      radio.write(&texte, sizeof(texte));
      Serial.println("✅ Paquet envoyé !");

      radio.startListening();
    } else {
      Serial.println("⚠️ (Radio non prêt)");
    }
  } 
  // 3. ACTION SI RELÂCHÉ
  else {
    Serial.print(" ➔ 🎧 MODE ÉCOUTE... ");

    if (nrfInitialise && radio.available()) {
      char texteRecu[32] = "";
      radio.read(&texteRecu, sizeof(texteRecu));
      Serial.print("📩 REÇU: ");
      Serial.println(texteRecu);
    } else {
      Serial.println(" Pas de message.");
    }
  }

  // Pause de 500 ms pour que ce soit facile à lire à l'œil nu
  delay(500); 
}