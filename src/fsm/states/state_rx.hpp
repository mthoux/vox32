#pragma once

#include "../state.hpp"

class StateRx : public State {
public:
    static StateRx& getInstance() {
        static StateRx instance;
        return instance;
    }

    void enter(Controller& controller) override;
    void update(Controller& controller, float dt) override;
    void exit(Controller& controller) override;

private:
    StateRx() = default;
};