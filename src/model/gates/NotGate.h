#ifndef NOTGATE_H
#define NOTGATE_H

#include "../LogicGate.h"

namespace model {
    class NotGate : public LogicGate {
    public:
        NotGate(const std::string& name = "NOT");
        void evaluate() override;
    };
}

#endif //NOTGATE_H