#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "timer.h"
#include "trigger.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#define UPPER_ROAD_BOUND 10
#define LOWER_ROAD_BOUND 3

typedef enum {
    STOP,
    TRIGGER_GO,
    GO,
    TRIGGER_STOP,
    WARNING,
    STOPPING
} IntersectionState;

typedef struct {
    IntersectionState state;
    char label;
    Trigger sensor;
    uint32_t timer;
} Road;

void road_init(Road *road, char label);
void road_stepState(Road *const road, bool goTrigger, bool stopTrigger);
void intersection_initQuery(Road **intersection, size_t *numRoads);
bool intersection_getNextPair(Road *intersection, size_t numRoads, Road **road1,
                              Road **road2);
void intersection_stepState(Road *intersection, size_t numRoads);

#endif
