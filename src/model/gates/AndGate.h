#ifndef ANDGATE_H
#define ANDGATE_H

#include "../LogicGate.h"

namespace model {
    class AndGate : public LogicGate {
    public:
        AndGate(const std::string& name = "AND");
        void evaluate() override;
    };
}

#endif //ANDGATE_H