#include "NotGate.h"

namespace model {
    NotGate::NotGate(const std::string& name)
        : LogicGate("NOT", name) {
        // Create 1 input pin and 1 output pin
        addInputPin("IN");
        addOutputPin("OUT");
    }
    
    void NotGate::evaluate() {
        // Get input state
        LogicState in = getInputPin(0)->getState();
        
        // Apply NOT logic
        LogicState result = LogicState::UNDEFINED;
        
        if (in == LogicState::HIGH) {
            result = LogicState::LOW;
        } else if (in == LogicState::LOW) {
            result = LogicState::HIGH;
        }
        
        // Set output state
        getOutputPin(0)->setState(result);
    }
}