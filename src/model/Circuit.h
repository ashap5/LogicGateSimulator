#ifndef CIRCUIT_H
#define CIRCUIT_H

#include "LogicGate.h"
#include <vector>
#include <memory>

namespace model {
    class Circuit {
    public:
        Circuit();
        ~Circuit();
        
        // Gate management
        void addGate(LogicGate* gate);
        void removeGate(LogicGate* gate);
        const std::vector<LogicGate*>& getGates() const;
        
        // Circuit simulation
        void simulate();
        
    private:
        std::vector<LogicGate*> gates;
        
        // Helper methods
        void topologicalSort(std::vector<LogicGate*>& sorted);
    };
}

#endif //CIRCUIT_H