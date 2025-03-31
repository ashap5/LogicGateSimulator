#include "AndGate.h"

namespace model {
    AndGate::AndGate(const std::string& name)
        : LogicGate("AND", name) {
        // Create 2 input pins and 1 output pin
        addInputPin("A");
        addInputPin("B");
        addOutputPin("OUT");
    }
    
    void AndGate::evaluate() {
        // Get input states
        LogicState a = getInputPin(0)->getState();
        LogicState b = getInputPin(1)->getState();
        
        // Apply AND logic
        LogicState result = LogicState::UNDEFINED;
        
        if (a == LogicState::LOW || b == LogicState::LOW) {
            result = LogicState::LOW;
        } else if (a == LogicState::HIGH && b == LogicState::HIGH) {
            result = LogicState::HIGH;
        }
        
        // Set output state
        getOutputPin(0)->setState(result);
    }
}