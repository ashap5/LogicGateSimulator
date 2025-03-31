// NorGate.h
#ifndef NORGATE_H
#define NORGATE_H

#include "../LogicGate.h"

namespace model {
    class NorGate : public LogicGate {
    public:
        NorGate(const std::string& name = "NOR");
        void evaluate() override;
    };
}

#endif //NORGATE_H