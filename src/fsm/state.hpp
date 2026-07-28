#pragma once

// Forward declaration
class Controller;

class State {
public:
    virtual ~State() = default;

    /**
     * @brief Returns the name of the state.
     */
    virtual const char* getName() const = 0;

    /**
     * @brief Called ONCE when entering this state.
     * Used to configure hardware (turn on LED, change RF mode, etc.)
     */
    virtual void enter(Controller& controller) {}

    /**
     * @brief Called in a LOOP as long as this state is active.
     * Used to read pins (polling) and execute logic.
     * @param controller Reference to the RadioController to request a state change.
     * @param dt Time elapsed since the last call (optional but useful for timers).
     */
    virtual void update(Controller& controller, float dt) = 0;

    /**
     * @brief Called ONCE when exiting this state.
     * Used to clean up (stop microphone, disable amplifiers, etc.)
     */
    virtual void exit(Controller& controller) {}
};