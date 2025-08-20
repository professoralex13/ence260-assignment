#include "intersection.h"
#include <stdint.h>
#include <stdio.h>

void road_init(Road *road, char label)
{
    road->label = label;
    road->state = STOP;
    road->sensor.label = label;
    road->sensor.state = false;
    road->timer = 0;

    trigger_register(&road->sensor);
    timer_register(&road->timer);
}

void road_stepState(Road *const road, bool goTrigger, bool stopTrigger)
{
    switch (road->state) {
        case STOP:
            if (goTrigger) {
                road->timer = 22;
                road->state = TRIGGER_GO;
            }
            break;
        case TRIGGER_GO:
            if (road->timer == 0) {
                road->state = GO;
            }
            break;
        case GO:
            if (stopTrigger) {
                road->timer = 15;
                road->state = TRIGGER_STOP;
            }
            break;
        case TRIGGER_STOP:
            if (road->timer == 0) {
                road->timer = 5;
                road->state = WARNING;
            }
            break;
        case WARNING:
            if (road->timer == 0) {
                road->timer = 2;
                road->state = STOPPING;
            }
            break;
        case STOPPING:
            if (road->timer == 0) {
                road->state = STOP;
            }
            break;
        default:
            road->state = STOP;
            road->timer = 0;
            break;
    }
}

void intersection_initQuery(Road **intersection, size_t *numRoads)
{
    printf("Traffic Light Simulator\n");

    bool looped = false;

    do {
        if (looped) {
            printf("Invalid, intersection size must be >%d <%d\n",
                   LOWER_ROAD_BOUND, UPPER_ROAD_BOUND);
        }

        printf("How many roads in the intersection: ");

        scanf("%zu", numRoads);

        looped = true;
    } while (*numRoads <= LOWER_ROAD_BOUND || *numRoads >= UPPER_ROAD_BOUND);

    *intersection = calloc(*numRoads, sizeof(Road));

    char current_label = 'A';

    for (size_t i = 0; i < *numRoads; i++) {
        road_init(&(*intersection)[i], current_label);

        current_label++;
    }
}

bool intersection_getNextPair(Road *intersection, size_t numRoads, Road **road1,
                              Road **road2)
{
    for (size_t i = 0; i < numRoads; i++) {
        if (&intersection[i] != *road1 && &intersection[i] != *road2 &&
            intersection[i].sensor.state) {
            *road1 = &intersection[i];
            *road2 = &intersection[(i + numRoads / 2) % numRoads];

            return true;
        }
    }

    return false;
}

void intersection_stepState(Road *intersection, size_t numRoads)
{
    static Road *road1;
    static Road *road2;

    bool shouldTransition =
        intersection_getNextPair(intersection, numRoads, &road1, &road2);

    for (size_t i = 0; i < numRoads; i++) {
        bool isTargetRoad =
            &intersection[i] == road1 || &intersection[i] == road2;

        road_stepState(&intersection[i], isTargetRoad && shouldTransition,
                       !isTargetRoad && shouldTransition);
    }
}
