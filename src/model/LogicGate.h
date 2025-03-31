#ifndef LOGICGATE_H
#define LOGICGATE_H

#include "Pin.h"
#include <vector>
#include <string>
#include <memory>

namespace model {
    class LogicGate {
    public:
        LogicGate(const std::string& type, const std::string& name);
        virtual ~LogicGate();
        
        // Gate identification
        std::string getType() const;
        std::string getName() const;
        void setName(const std::string& name);
        
        // Pin management
        const std::vector<Pin*>& getInputPins() const;
        const std::vector<Pin*>& getOutputPins() const;
        Pin* getInputPin(int index) const;
        Pin* getOutputPin(int index) const;
        
        // Logic evaluation
        virtual void evaluate() = 0;
        
    protected:
        // Helper methods for derived classes
        void addInputPin(const std::string& name);
        void addOutputPin(const std::string& name);
        
    private:
        std::string type;
        std::string name;
        std::vector<Pin*> inputPins;
        std::vector<Pin*> outputPins;
    };
}

#endif //LOGICGATE_H