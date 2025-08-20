#ifndef TRIGGER_H
#define TRIGGER_H

#include <stdbool.h>

#define MAX_TRIGGERS 100

typedef struct {
    bool state;
    char label;
} Trigger;

void trigger_register(Trigger *trigger);
void trigger_resetAll(void);
void trigger_set(char id);

#endif