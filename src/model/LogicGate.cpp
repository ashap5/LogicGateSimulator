#include "LogicGate.h"

namespace model {
    LogicGate::LogicGate(const std::string& type, const std::string& name)
        : type(type), name(name) {
    }
    
    LogicGate::~LogicGate() {
        for (auto* pin : inputPins) {
            delete pin;
        }
        for (auto* pin : outputPins) {
            delete pin;
        }
    }
    
    std::string LogicGate::getType() const {
        return type;
    }
    
    std::string LogicGate::getName() const {
        return name;
    }
    
    void LogicGate::setName(const std::string& newName) {
        name = newName;
    }
    
    const std::vector<Pin*>& LogicGate::getInputPins() const {
        return inputPins;
    }
    
    const std::vector<Pin*>& LogicGate::getOutputPins() const {
        return outputPins;
    }
    
    Pin* LogicGate::getInputPin(int index) const {
        if (index >= 0 && index < inputPins.size()) {
            return inputPins[index];
        }
        return nullptr;
    }
    
    Pin* LogicGate::getOutputPin(int index) const {
        if (index >= 0 && index < outputPins.size()) {
            return outputPins[index];
        }
        return nullptr;
    }
    
    void LogicGate::addInputPin(const std::string& name) {
        inputPins.push_back(new Pin(this, PinType::INPUT, name));
    }
    
    void LogicGate::addOutputPin(const std::string& name) {
        outputPins.push_back(new Pin(this, PinType::OUTPUT, name));
    }
}