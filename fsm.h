#ifndef FSM_H
#define FSM_H

#include <stdint.h>
#include <stdbool.h>
#include "timer.h"
#include "trigger.h"

typedef enum {
    STOP, TRIGGER_GO, GO, TRIGGER_STOP, WARNING, STOPPING, NUM_STATES, ERROR_STATE
} State;

typedef enum {
    GO_TRIGGER, STOP_TRIGGER, TIMEOUT, NUM_TRIGGERS
} Triggers;

typedef enum {
    RED, YELLOW, GREEN, NUM_LIGHTS
} Lights;

#define STATENAME(s) (s == STOP ? "STOP" : (s == TRIGGER_GO ? "TRIGGER_GO" : (s == GO ? "GO" : (s == TRIGGER_STOP ? "TRIGGER_STOP" : (s == WARNING ? "WARNING" : (s == STOPPING ? "STOPPING" : "ERROR"))))))


typedef bool Events[NUM_TRIGGERS];
typedef struct {
	char label;
	Lights light;
	uint32_t timer;
	Trigger sensor;
} FsmIO;

typedef State (*TransitionFunc)(Events);
typedef FsmIO (*OutputFunc)(Events);

typedef struct {
	State currentState;
	FsmIO* io;
	TransitionFunc transitionFuncs[NUM_STATES];
	OutputFunc outputFuncs[NUM_STATES];
} Fsm;

void io_init(char label, FsmIO* io);
Fsm fsm_init(State initState, FsmIO* io);
void fsm_processEvent(Fsm* fsm, Events events);
void fsm_addTransition(Fsm* fsm, State fromState, TransitionFunc transitionFunc, OutputFunc outputFunc);


#endif // FSM_H
