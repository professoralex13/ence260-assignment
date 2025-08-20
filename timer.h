#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>

#define MAX_TIMERS 100

void timer_register(uint32_t *timer);
void timer_updateAll(void);

#endif