#include <iostream>
#include <thread>
#include <chrono>

#include "fsm/controller.hpp"
#include "fsm/states/state_idle.hpp"

// Include Mocks instead of hardware ESP32 classes
#include "hal/mock/mock_input.hpp"
#include "hal/mock/mock_output.hpp"
#include "hal/mock/mock_radio.hpp"
#include "hal/mock/mock_micro.hpp"

int main() {
    std::cout << "=== 🖥️ VOX32 FSM SIMULATION ===" << std::endl;

    // 1. Instantiate Mock implementations
    MockInput  mockInput;
    MockOutput mockOutput;
    MockRadio  mockRadio;
    MockMicro mockMicro;

    // 2. Inject dependencies into the Controller
    Controller controller(mockInput, mockOutput, mockRadio, mockMicro);
    controller.init(StateIdle::getInstance());

    // 3. Simulation loop (simulates 5 seconds of runtime)
    float dt = 0.1f; // 100ms per tick
    
    for (int i = 0; i < 50; ++i) {
        // Interactive test scenario:
        if (i == 5) {
            std::cout << "👉 [TEST] User presses the PTT button!" << std::endl;
            mockInput.buttonState = true;
        } 
        else if (i == 15) {
            std::cout << "👉 [TEST] User releases the PTT button!" << std::endl;
            mockInput.buttonState = false;
        } 
        
        // Update FSM logic
        controller.update(dt);

        // 100ms delay to simulate real-time execution
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }

    std::cout << "\n=== End of simulation ===" << std::endl;
    return 0;
}