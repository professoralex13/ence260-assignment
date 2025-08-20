#ifndef FSMROAD_H
#define FSMROAD_H 1

#include "fsm.h"

State stopTransition(Events events);
State triggerGoTransition(Events events);
FsmIO stopOutput(Events events);
FsmIO triggerGoOutput(Events events);


#endif // FSMROAD_H