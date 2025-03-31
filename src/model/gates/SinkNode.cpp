#include "SinkNode.h"

namespace model {
    SinkNode::SinkNode(const std::string& name)
        : LogicGate("SINK", name) {
        // Create 1 input pin
        addInputPin("IN");
    }
    
    void SinkNode::evaluate() {
        // Sink node doesn't need any evaluation, it just receives input
    }
    
    LogicState SinkNode::getState() const {
        return getInputPin(0)->getState();
    }
}