// XorGate.cpp
#include "XorGate.h"

namespace model {
    XorGate::XorGate(const std::string& name)
        : LogicGate("XOR", name) {
        // Create 2 input pins and 1 output pin
        addInputPin("A");
        addInputPin("B");
        addOutputPin("OUT");
    }

    void XorGate::evaluate() {
        // Get input states
        LogicState a = getInputPin(0)->getState();
        LogicState b = getInputPin(1)->getState();

        // Apply XOR logic
        LogicState result = LogicState::UNDEFINED;

        if (a == LogicState::UNDEFINED || b == LogicState::UNDEFINED) {
            result = LogicState::UNDEFINED;
        } else if (a == b) {
            result = LogicState::LOW;
        } else {
            result = LogicState::HIGH;
        }

        // Set output state
        getOutputPin(0)->setState(result);
    }
}