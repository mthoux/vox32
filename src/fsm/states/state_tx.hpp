#pragma once

#include "../state.hpp"

class StateTx : public State {
public:
    static StateTx& getInstance() {
        static StateTx instance;
        return instance;
    }

    void enter(Controller& controller) override;
    void update(Controller& controller, float dt) override;
    void exit(Controller& controller) override;

private:
    StateTx() = default;
};