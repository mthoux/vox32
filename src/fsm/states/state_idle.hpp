#pragma once
#include "../state.hpp"

class StateIdle : public State {
public:
    // Permet de récupérer l'unique instance de cet état
    static StateIdle& getInstance() {
        static StateIdle instance;
        return instance;
    }

    void enter(RadioController& controller) override;
    void update(RadioController& controller, float dt) override;
    void exit(RadioController& controller) override;

private:
    StateIdle() = default; // Constructeur privé -> Personne ne peut instancier un 2ème StateIdle
};