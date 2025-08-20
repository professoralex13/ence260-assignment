#include "fsmRoad.h"


State stopTransition(Events events)
{
    if (events[GO_TRIGGER]) {
        return TRIGGER_GO;
    }

    return STOP;
}

State triggerGoTransition(Events events)
{
    if (events[TIMEOUT]) {
        return GO;
    }

    return TRIGGER_GO;
}


FsmIO stopOutput(Events events)
{
    FsmIO io;

    if (events[GO_TRIGGER]) {
        io.light = RED;
        io.timer = 22;
    } else {
        io.light = RED;
        io.timer = 0;
    }
    return io;
}

FsmIO triggerGoOutput(Events events)
{
    FsmIO io;

    if (events[TIMEOUT]) {
        io.light = GREEN;
        io.timer = 0;
    } else {
        io.light = RED;
        io.timer = 0;
    }
    return io;
}



