#ifndef LOGICSTATE_H
#define LOGICSTATE_H

namespace model {
    enum class LogicState {
        LOW,        // Logic 0
        HIGH,       // Logic 1
        UNDEFINED   // Uninitialized or error state
    };
}

#endif //LOGICSTATE_H