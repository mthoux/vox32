#include <Arduino.h>
#include <SPI.h>
#include <RF24.h>
#include "pins.hpp"

// FSM & Core
#include "fsm/controller.hpp"
#include "fsm/states/state_idle.hpp"

// Hardware Abstraction Layer (ESP32)
#include "hal/esp32/esp32_input.hpp"
#include "hal/esp32/esp32_output.hpp"
#include "hal/esp32/esp32_radio.hpp"
#include "hal/mock/mock_micro.hpp"
#include "hal/mock/mock_speaker.hpp"

// 1. Instantiate physical NRF24 hardware instance
RF24 hardwareRadio(PIN_CE, PIN_SPI_CSN);

// 2. Instantiate HAL objects
Esp32Input  espInput(PIN_BTN);
Esp32Output espOutput(PIN_BLUE_LED, PIN_GREEN_LED);
Esp32Radio  espRadio(hardwareRadio);
MockMicro   mockMicro;
MockSpeaker mockSpeaker;

// 3. Inject dependencies into Controller
Controller controller(espInput, espOutput, espRadio, mockMicro, mockSpeaker);

const byte radioAddress[6] = "00001";

void setup() {
    Serial.begin(115200);
    delay(200);

    // Initialize inputs and outputs via HAL
    espInput.init();
    espOutput.init();

    // Startup visual confirmation flash
    espOutput.setRxLed(true);
    espOutput.setTxLed(true);
    delay(300);
    espOutput.setRxLed(false);
    espOutput.setTxLed(false);

    // Initialize SPI bus and Radio module
    SPI.begin(PIN_SPI_SCK, PIN_SPI_MOSI, PIN_SPI_MISO);

    if (hardwareRadio.begin()) {
        // NRF24 Configuration
        hardwareRadio.setPALevel(RF24_PA_LOW);
        hardwareRadio.setAutoAck(false);
        hardwareRadio.setRetries(0, 0);

        hardwareRadio.openWritingPipe(radioAddress);
        hardwareRadio.openReadingPipe(1, radioAddress);
        hardwareRadio.startListening();

        Serial.println("🟢 Radio ready!");
    } else {
        Serial.println("🔴 NRF24 initialization error");
    }

    // Initialize FSM in IDLE state
    controller.init(StateIdle::getInstance());
}

void loop() {
    // Delta time calculation (dt)
    static uint32_t lastTimeMs = millis();
    uint32_t now = millis();

    float dt = (now - lastTimeMs) / 1000.0f;
    lastTimeMs = now;

    // Update FSM controller
    controller.update(dt);
}