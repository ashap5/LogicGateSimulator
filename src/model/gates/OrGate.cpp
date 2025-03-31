#include "OrGate.h"

namespace model {
    OrGate::OrGate(const std::string& name)
        : LogicGate("OR", name) {
        // Create 2 input pins and 1 output pin
        addInputPin("A");
        addInputPin("B");
        addOutputPin("OUT");
    }
    
    void OrGate::evaluate() {
        // Get input states
        LogicState a = getInputPin(0)->getState();
        LogicState b = getInputPin(1)->getState();
        
        // Apply OR logic
        LogicState result = LogicState::UNDEFINED;
        
        if (a == LogicState::HIGH || b == LogicState::HIGH) {
            result = LogicState::HIGH;
        } else if (a == LogicState::LOW && b == LogicState::LOW) {
            result = LogicState::LOW;
        }
        
        // Set output state
        getOutputPin(0)->setState(result);
    }
}