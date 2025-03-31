#ifndef PIN_H
#define PIN_H

#include "LogicState.h"
#include <vector>
#include <memory>
#include <string>

namespace model {
    
    class Connection;
    class LogicGate;
    
    enum class PinType {
        INPUT,
        OUTPUT
    };
    
    class Pin {
    public:
        Pin(LogicGate* parent, PinType type, const std::string& name);
        ~Pin();
        
        // Getters
        LogicState getState() const;
        PinType getType() const;
        std::string getName() const;
        LogicGate* getParent() const;
        
        // Connection management
        bool canConnect(Pin* other) const;
        bool connect(Pin* other);
        void disconnect(Pin* other);
        const std::vector<Connection*>& getConnections() const;
        
        // State management
        void setState(LogicState state);
        void propagateState();
        
    private:
        LogicGate* parent;
        PinType type;
        std::string name;
        LogicState state;
        std::vector<Connection*> connections;
    };
}

#endif //PIN_H