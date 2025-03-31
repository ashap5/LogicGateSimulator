// NandGate.cpp
#include "NandGate.h"

namespace model {
    NandGate::NandGate(const std::string& name)
        : LogicGate("NAND", name) {
        // Create 2 input pins and 1 output pin
        addInputPin("A");
        addInputPin("B");
        addOutputPin("OUT");
    }

    void NandGate::evaluate() {
        // Get input states
        LogicState a = getInputPin(0)->getState();
        LogicState b = getInputPin(1)->getState();

        // Apply NAND logic
        LogicState result = LogicState::UNDEFINED;

        if (a == LogicState::HIGH && b == LogicState::HIGH) {
            result = LogicState::LOW;
        } else if (a == LogicState::LOW || b == LogicState::LOW) {
            result = LogicState::HIGH;
        }

        // Set output state
        getOutputPin(0)->setState(result);
    }
}