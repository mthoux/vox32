#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include <pins.h>
#include "fsm/controller.hpp"
#include "fsm/states/state_idle.hpp"

RF24 radio(PIN_CE, PIN_SPI_CSN);
Controller controller(radio);
const byte adresse[6] = "00001";

void setup() {
  Serial.begin(115200);
  delay(200); 

  pinMode(PIN_BTN, INPUT_PULLUP);
  pinMode(PIN_GREEN_LED, OUTPUT);
  pinMode(PIN_BLUE_LED, OUTPUT);

  // Flash de démarrage
  digitalWrite(PIN_GREEN_LED, HIGH);
  digitalWrite(PIN_BLUE_LED, HIGH);
  delay(300);
  digitalWrite(PIN_GREEN_LED, LOW);
  digitalWrite(PIN_BLUE_LED, LOW);

  SPI.begin(PIN_SPI_SCK, PIN_SPI_MOSI, PIN_SPI_MISO);

  if (radio.begin()) {
    
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

  controller.init(StateIdle::getInstance());
}

void loop() {
  controller.update();
}