#include <stdint.h>
#include <stdlib.h>

#define MAX_TIMERS 100

static uint32_t *allTimers[MAX_TIMERS];

static size_t numTimers = 0;

void timer_register(uint32_t *timer)
{
    if (numTimers >= MAX_TIMERS) {
        return;
    }

    allTimers[numTimers] = timer;
    numTimers++;
}

void timer_updateAll(void)
{
    for (size_t i = 0; i < numTimers; i++) {
        if (*allTimers[i] > 0) {
            *allTimers[i] -= 1;
        }
    }
}
