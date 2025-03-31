#ifndef CONNECTION_H
#define CONNECTION_H

#include "Pin.h"

namespace model {
    class Connection {
    public:
        Connection(Pin* source, Pin* destination);
        ~Connection();
        
        // Getters
        Pin* getSource() const;
        Pin* getDestination() const;
        
        // Propagation
        void propagateState();
        
    private:
        Pin* source;      // Output pin
        Pin* destination; // Input pin
    };
}

#endif //CONNECTION_H