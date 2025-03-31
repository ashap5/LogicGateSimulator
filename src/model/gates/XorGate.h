// XorGate.h
#ifndef XORGATE_H
#define XORGATE_H

#include "../LogicGate.h"

namespace model {
    class XorGate : public LogicGate {
    public:
        XorGate(const std::string& name = "XOR");
        void evaluate() override;
    };
}

#endif //XORGATE_H