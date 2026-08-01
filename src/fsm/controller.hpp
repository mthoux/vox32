#pragma once

#include <cstdint>

#include "hal/interfaces/i_input.hpp"
#include "hal/interfaces/i_output.hpp"
#include "hal/interfaces/i_radio.hpp"
#include "hal/interfaces/i_micro.hpp"
#include "hal/interfaces/i_speaker.hpp"

#include "state.hpp"
#include "pins.hpp"

class Controller {
private:
    State* currentState = nullptr;
    float time_elapsed = 0;

    IInput& input;
    IOutput& output;
    IRadio& radio;
    IMicro& micro;
    ISpeaker& speaker;

public:
    Controller(IInput& inputDevice, IOutput& outputDevice, IRadio& radioDevice, IMicro& microDevice, ISpeaker& speakerDevice) : 
        input(inputDevice), output(outputDevice), radio(radioDevice), micro(microDevice), speaker(speakerDevice) {}

    /**
     * @brief Initialize the controller with the starting state (e.g., StateIdle)
     */
    void init(State& initialState);

    /**
     * @brief To be called in a loop within main (while(true))
     */
    void update(float dt);

    /**
     * @brief Perform the transition to a new state
     */
    void changeState(State& newState);

    /**
     * @brief Get the current state (useful for debugging/logs)
     */
    State* getCurrentState() const { return currentState; }

    IInput&  getInput()  { return input;  }
    IOutput& getOutput() { return output; }
    IRadio&  getRadio()  { return radio;  }
    IMicro&  getMicro()  { return micro;  }
};