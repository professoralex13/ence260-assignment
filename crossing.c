#include "crossing.h"
#include <stdint.h>
#include <stdio.h>

void crossing_init(Crossing *crossing, char label)
{
    crossing->label = label;
    crossing->state = IDLE;
    crossing->button.label = label;
    crossing->button.state = false;
    crossing->timer = 0;

    trigger_register(&crossing->button);
    timer_register(&crossing->timer);
}

void crossing_stepState(Crossing *crossing, Trigger *trigger)
{
    switch (crossing->state) {
        case IDLE:
            if (trigger->state) {
                crossing->timer = 15;
                crossing->state = STOP;
            }
            break;
        case STOP:
            if (crossing->timer == 0) {
                crossing->timer = 10;
                crossing->state = GO;
            }
            break;
        case GO:
            if (crossing->timer == 0) {
                crossing->timer = 5;
                crossing->state = HURRY;
            }
            break;
        case HURRY:
            if (crossing->timer == 0) {
                crossing->state = IDLE;
            }
            break;
        default:
            crossing->state = IDLE;
            crossing->timer = 0;
            break;
    }
}
