#include "Pin.h"
#include "Connection.h"
#include "LogicGate.h"
#include <algorithm>

namespace model {
    Pin::Pin(LogicGate* parent, PinType type, const std::string& name)
        : parent(parent), type(type), name(name), state(LogicState::UNDEFINED) {
    }
    
    Pin::~Pin() {
        // Just clear the vector without deleting connections
        connections.clear();
    }
    
    LogicState Pin::getState() const {
        return state;
    }
    
    PinType Pin::getType() const {
        return type;
    }
    
    std::string Pin::getName() const {
        return name;
    }
    
    LogicGate* Pin::getParent() const {
        return parent;
    }
    
    bool Pin::canConnect(Pin* other) const {
        // Can only connect input to output or output to input
        return other != nullptr && 
               this->type != other->type &&
               (this->type == PinType::OUTPUT || other->type == PinType::OUTPUT);
    }
    
    bool Pin::connect(Pin* other) {
        if (!canConnect(other)) {
            return false;
        }
        
        // Create new connection
        Connection* connection = new Connection(
            (this->type == PinType::OUTPUT) ? this : other,
            (this->type == PinType::INPUT) ? this : other
        );
        
        // Add the connection to both pins
        connections.push_back(connection);
        other->connections.push_back(connection);
        
        // Propagate state from output to input
        if (this->type == PinType::OUTPUT) {
            connection->propagateState();
        } else {
            other->propagateState();
        }
        
        return true;
    }
    
    void Pin::disconnect(Pin* other) {
        for (auto it = connections.begin(); it != connections.end(); ) {
            Connection* conn = *it;
            if (conn->getSource() == other || conn->getDestination() == other) {
                // Find and remove the connection from the other pin as well
                auto& otherConnections = other->connections;
                auto otherIt = std::find(otherConnections.begin(), otherConnections.end(), conn);
                if (otherIt != otherConnections.end()) {
                    otherConnections.erase(otherIt);
                }
                
                // Delete the connection and remove it from this pin
                delete conn;
                it = connections.erase(it);
            } else {
                ++it;
            }
        }
        
        // Reset input pin to undefined when disconnected
        if (this->type == PinType::INPUT) {
            setState(LogicState::UNDEFINED);
        }
    }
    
    const std::vector<Connection*>& Pin::getConnections() const {
        return connections;
    }
    
    void Pin::setState(LogicState newState) {
        if (state != newState) {
            state = newState;
            if (type == PinType::OUTPUT) {
                propagateState();
            }
        }
    }
    
    void Pin::propagateState() {
        if (type == PinType::OUTPUT) {
            for (auto* connection : connections) {
                connection->propagateState();
            }
        }
    }
}