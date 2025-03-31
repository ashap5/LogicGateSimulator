#include "SourceNode.h"

namespace model {
    SourceNode::SourceNode(LogicState initialState, const std::string& name)
        : LogicGate("SOURCE", name), state(initialState) {
        // Create 1 output pin
        addOutputPin("OUT");
        getOutputPin(0)->setState(state);
    }
    
    void SourceNode::evaluate() {
        // Source node doesn't need evaluation, just maintain its state
        getOutputPin(0)->setState(state);
    }
    
    void SourceNode::toggleState() {
        if (state == LogicState::HIGH) {
            setState(LogicState::LOW);
        } else {
            setState(LogicState::HIGH);
        }
    }
    
    void SourceNode::setState(LogicState newState) {
        state = newState;
        getOutputPin(0)->setState(state);
    }
    
    LogicState SourceNode::getState() const {
        return state;
    }
}