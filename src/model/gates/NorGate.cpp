// NorGate.cpp
#include "NorGate.h"

namespace model {
    NorGate::NorGate(const std::string& name)
        : LogicGate("NOR", name) {
        // Create 2 input pins and 1 output pin
        addInputPin("A");
        addInputPin("B");
        addOutputPin("OUT");
    }

    void NorGate::evaluate() {
        // Get input states
        LogicState a = getInputPin(0)->getState();
        LogicState b = getInputPin(1)->getState();

        // Apply NOR logic
        LogicState result = LogicState::UNDEFINED;

        if (a == LogicState::LOW && b == LogicState::LOW) {
            result = LogicState::HIGH;
        } else if (a == LogicState::HIGH || b == LogicState::HIGH) {
            result = LogicState::LOW;
        }

        // Set output state
        getOutputPin(0)->setState(result);
    }
}