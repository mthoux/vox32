#pragma once

#include "state.hpp"
#include <cstdint>

class Controller {
private:
    State* currentState = nullptr;
    uint32_t lastTimeMs = 0;

public:
    Controller() = default;

    /**
     * @brief Initialise le contrôleur avec l'état de démarrage (ex: StateIdle)
     */
    void init(State& initialState);

    /**
     * @brief À appeler en boucle dans le main (while(true))
     */
    void update();

    /**
     * @brief Effectue la transition vers un nouvel état
     */
    void changeState(State& newState);

    /**
     * @brief Permet de connaître l'état actuel (utile pour le debug/logs)
     */
    State* getCurrentState() const { return currentState; }
};