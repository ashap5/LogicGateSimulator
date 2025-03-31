#ifndef SOURCENODE_H
#define SOURCENODE_H

#include "../LogicGate.h"

namespace model {
    class SourceNode : public LogicGate {
    public:
        SourceNode(LogicState initialState, const std::string& name = "Source");
        
        void evaluate() override;
        void toggleState();
        void setState(LogicState state);
        LogicState getState() const;
        
    private:
        LogicState state;
    };
}

#endif //SOURCENODE_H