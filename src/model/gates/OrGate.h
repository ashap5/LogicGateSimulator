#ifndef ORGATE_H
#define ORGATE_H

#include "../LogicGate.h"

namespace model {
    class OrGate : public LogicGate {
    public:
        OrGate(const std::string& name = "OR");
        void evaluate() override;
    };
}

#endif //ORGATE_H