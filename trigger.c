#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_TRIGGERS 100

typedef struct {
    bool state;
    char label;
} Trigger;

static Trigger *allTriggers[MAX_TRIGGERS];

static size_t numTriggers = 0;

void trigger_register(Trigger *trigger)
{
    if (numTriggers >= MAX_TRIGGERS) {
        return;
    }

    allTriggers[numTriggers] = trigger;
    numTriggers++;
}

void trigger_resetAll(void)
{
    for (size_t i = 0; i < numTriggers; i++) {
        allTriggers[i]->state = false;
    }
}

void trigger_set(char id)
{
    for (size_t i = 0; i < numTriggers; i++) {
        if (allTriggers[i]->label == id) {
            allTriggers[i]->state = true;
        }
    }
}
