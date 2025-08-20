#include "trigger.c" // TODO: Switch this to trigger.h once header files are created
#include <stdint.h>

typedef enum { IDLE, STOP, GO, HURRY } CrossingState;

typedef struct {
    CrossingState state;
    char label;
    Trigger *button;
    uint32_t *timer;
} Crossing;