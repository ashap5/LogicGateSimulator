// NandGate.h
#ifndef NANDGATE_H
#define NANDGATE_H

#include "../LogicGate.h"

namespace model {
    class NandGate : public LogicGate {
    public:
        NandGate(const std::string& name = "NAND");
        void evaluate() override;
    };
}

#endif //NANDGATE_H