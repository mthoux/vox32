#pragma once

#include <cstdint>

#include "i_input.hpp"
#include "i_output.hpp"
#include "i_radio.hpp"

#include "state.hpp"
#include "pins.h"

class Controller {
private:
    State* currentState = nullptr;

    IInput& input;
    IOutput& output;
    IRadio& radio;

public:
    Controller(IInput& inputDevice, IOutput& outputDevice, IRadio& radioDevice) : 
        input(inputDevice), output(outputDevice), radio(radioDevice) {}

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
};