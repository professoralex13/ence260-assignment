#include <stdint.h>
#include <stdio.h>

#include "fsm.h"

void io_init(char label, FsmIO *io)
{
    io->label = label;
    io->light = RED;
    io->timer = 0;
    io->sensor.label = label;
    timer_register(&(io->timer));
    trigger_register(&(io->sensor));
}

Fsm fsm_init(State initState, FsmIO *io)
{
    Fsm fsm;
    fsm.currentState = initState;
    fsm.io = io;
    for (size_t i = 0; i < NUM_STATES; i++) {
        fsm.transitionFuncs[i] = NULL;
        fsm.outputFuncs[i] = NULL;
    }
    return fsm;
}

void fsm_addTransition(Fsm *fsm, State fromState, TransitionFunc transitionFunc,
                       OutputFunc outputFunc)
{
    fsm->transitionFuncs[fromState] = transitionFunc;
    fsm->outputFuncs[fromState] = outputFunc;
}

void fsm_processEvent(Fsm *fsm, Events events)
{
    State newState = fsm->transitionFuncs[fsm->currentState](events);
    FsmIO output = fsm->outputFuncs[fsm->currentState](events);

    fsm->currentState = newState;
    fsm->io->light = output.light;

    if (output.timer != 0) {
        fsm->io->timer = output.timer;
    }
}
