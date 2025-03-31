#include "Circuit.h"
#include <algorithm>
#include <unordered_set>
#include <unordered_map>
#include <functional>
#include "Connection.h"
namespace model {
    Circuit::Circuit() {
    }
    
    Circuit::~Circuit() {
        for (auto* gate : gates) {
            delete gate;
        }
    }
    
    void Circuit::addGate(LogicGate* gate) {
        gates.push_back(gate);
    }
    
    void Circuit::removeGate(LogicGate* gate) {
        auto it = std::find(gates.begin(), gates.end(), gate);
        if (it != gates.end()) {
            gates.erase(it);
            delete gate;
        }
    }
    
    const std::vector<LogicGate*>& Circuit::getGates() const {
        return gates;
    }
    
    void Circuit::simulate() {
        // Sort gates to ensure proper evaluation order
        std::vector<LogicGate*> sortedGates;
        topologicalSort(sortedGates);
        
        // Evaluate each gate in the sorted order
        for (LogicGate* gate : sortedGates) {
            gate->evaluate();
        }
    }
    
    void Circuit::topologicalSort(std::vector<LogicGate*>& sorted) {
        sorted.clear();
        
        std::unordered_map<LogicGate*, std::unordered_set<LogicGate*>> dependencies;
        std::unordered_set<LogicGate*> visited;
        
        // Build dependency graph
        for (LogicGate* gate : gates) {
            dependencies[gate] = {};
            
            // For each input pin of this gate
            for (Pin* inputPin : gate->getInputPins()) {
                // Find all gates that connect to this input pin
                for (Connection* connection : inputPin->getConnections()) {
                    LogicGate* sourceGate = connection->getSource()->getParent();
                    if (sourceGate != gate) {
                        dependencies[gate].insert(sourceGate);
                    }
                }
            }
        }
        
        // Depth-first search to build sorted list
        std::function<void(LogicGate*)> dfs = [&](LogicGate* gate) {
            if (visited.find(gate) != visited.end()) return;
            
            visited.insert(gate);
            
            for (LogicGate* dep : dependencies[gate]) {
                dfs(dep);
            }
            
            sorted.push_back(gate);
        };
        
        // Process all gates
        for (LogicGate* gate : gates) {
            if (visited.find(gate) == visited.end()) {
                dfs(gate);
            }
        }
        
        // Reverse to get correct order (dependencies first)
        std::reverse(sorted.begin(), sorted.end());
    }
}