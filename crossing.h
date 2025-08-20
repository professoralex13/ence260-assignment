#ifndef CROSSING_H
#define CROSSING_H

#include "timer.h"
#include "trigger.h"
#include <stdint.h>

typedef enum { IDLE, STOP, GO, HURRY } CrossingState;

typedef struct {
    CrossingState state;
    char label;
    Trigger button;
    uint32_t timer;
} Crossing;

void crossing_init(Crossing *crossing, char label);
void crossing_stepState(Crossing *crossing, Trigger *trigger);

#endif
