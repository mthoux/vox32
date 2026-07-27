#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>

#define PIN_CE        4
#define PIN_CSN       5
#define PIN_PTT       21 
#define PIN_BLUE_LED  16 
#define PIN_GREEN_LED 17 

RF24 radio(PIN_CE, PIN_CSN);
bool nrfInitialise = false;
const byte adresse[6] = "00001";

void setup() {
  Serial.begin(115200);
  delay(1000); 

  pinMode(PIN_PTT, INPUT_PULLUP);
  pinMode(PIN_GREEN_LED, OUTPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);

  // Flash de démarrage
  digitalWrite(PIN_GREEN_LED, HIGH);
  digitalWrite(PIN_BLUE_LED, HIGH);
  delay(300);
  digitalWrite(PIN_GREEN_LED, LOW);
  digitalWrite(PIN_BLUE_LED, LOW);

  SPI.begin(18, 19, 23);

  if (radio.begin()) {
    nrfInitialise = true;
    
    // Configuration pour envoi direct sans attente d'Acknowledge
    radio.setPALevel(RF24_PA_LOW);
    radio.setAutoAck(false); 
    radio.setRetries(0, 0); 
    
    radio.openWritingPipe(adresse);
    radio.openReadingPipe(1, adresse);
    radio.startListening();
    
    Serial.println("🟢 Radio prêt !");
  } else {
    Serial.println("🔴 Erreur NRF24");
  }
}

void loop() {
  int etatBouton = digitalRead(PIN_PTT);

  // --- MODE ÉMISSION ---
  if (etatBouton == LOW) {
    digitalWrite(PIN_GREEN_LED, HIGH);

    if (nrfInitialise) {
      radio.stopListening();
      const char texte[] = "PING!";
      
      radio.write(&texte, sizeof(texte));
      Serial.println("📡 Message 'PING!' envoyé !");
      
      radio.startListening();
    }
  } 
  // --- MODE ÉCOUTE ---
  else {
    digitalWrite(PIN_GREEN_LED, LOW);

    if (nrfInitialise && radio.available()) {
      digitalWrite(PIN_BLUE_LED, HIGH);

      char texteRecu[32] = "";
      radio.read(&texteRecu, sizeof(texteRecu));
      
      Serial.print("📩 Message reçu: ");
      Serial.println(texteRecu);

      delay(150);

      digitalWrite(PIN_BLUE_LED, LOW);
    }
  }
}