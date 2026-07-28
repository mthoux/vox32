#pragma once

#include "../state.hpp"

class StateIdle : public State {
public:
    static StateIdle& getInstance() {
        static StateIdle instance;
        return instance;
    }

    const char* getName() const override { return "Idle"; }

    void enter(Controller& controller) override;
    void update(Controller& controller, float dt) override;
    void exit(Controller& controller) override;

private:
    StateIdle() = default;
};