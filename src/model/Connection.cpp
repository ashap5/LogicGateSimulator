#include "Connection.h"

namespace model {
    Connection::Connection(Pin* source, Pin* destination)
        : source(source), destination(destination) {
    }
    
    Connection::~Connection() {
        // Connection destructor doesn't delete pins
        // Pins are owned by their parent gates
    }
    
    Pin* Connection::getSource() const {
        return source;
    }
    
    Pin* Connection::getDestination() const {
        return destination;
    }
    
    void Connection::propagateState() {
        if (source && destination) {
            destination->setState(source->getState());
        }
    }
}