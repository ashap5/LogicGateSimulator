#ifndef SINKNODE_H
#define SINKNODE_H

#include "../LogicGate.h"

namespace model {
    class SinkNode : public LogicGate {
    public:
        SinkNode(const std::string& name = "Sink");
        void evaluate() override;
        LogicState getState() const;
    };
}

#endif //SINKNODE_H