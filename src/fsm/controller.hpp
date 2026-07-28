#pragma once

#include <cstdint>

#include "hal/interfaces/i_input.hpp"
#include "hal/interfaces/i_output.hpp"
#include "hal/interfaces/i_radio.hpp"
#include "hal/interfaces/i_micro.hpp"

#include "state.hpp"
#include "pins.hpp"

class Controller {
private:
    State* currentState = nullptr;

    IInput& input;
    IOutput& output;
    IRadio& radio;
    IMicro& micro;

public:
    Controller(IInput& inputDevice, IOutput& outputDevice, IRadio& radioDevice, IMicro& microDevice) : 
        input(inputDevice), output(outputDevice), radio(radioDevice), micro(microDevice) {}

    /**
     * @brief Initialise le contrôleur avec l'état de démarrage (ex: StateIdle)
     */
    void init(State& initialState);

    /**
     * @brief À appeler en boucle dans le main (while(true))
     */
    void update(float dt);

    /**
     * @brief Effectue la transition vers un nouvel état
     */
    void changeState(State& newState);

    /**
     * @brief Permet de connaître l'état actuel (utile pour le debug/logs)
     */
    State* getCurrentState() const { return currentState; }

    IInput&  getInput()  { return input;  }
    IOutput& getOutput() { return output; }
    IRadio&  getRadio()  { return radio;  }
    IMicro&  getMicro()  { return micro;  }
};