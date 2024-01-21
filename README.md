# Small Finite State Machine
Just a very simple finite state machine library in C.

Functionality is somewhat limited by design, and functions that get the current state, return codes, convert states to strings, etc must be implemented by the application.

## Example
To initialise and execute the following FSM:
```
                        /---------\
                       v           \
+======+         +------+         +---------+
||INIT||-------->| WAIT |-------->| TIMEOUT |
+======+         +------+         +---------+
   ^             / |  ^
   |            /  |  |
   |     /-----/   |  |
   |    /          |  |
   |   v           v  |
+-------+        +-------+
| ERROR |<-------| READY |
+-------+        +-------+
```

The below code may be used:
```c
#include "fsm.h"

int main(void) {
    FiniteStateMachine fsm;

    StateTransition transition_table[] = {
        {init_state, 0, wait_state},
        {wait_state, 0, ready_state},
        {wait_state, 1, error_state},
        {wait_state, 2, timeout_state},
        {ready_state, 0, wait_state},
        {ready_state, 1, error_state},
        {timeout_state, 0, wait_state},
        {error_state, 2, init_state},
    };

    if (initialise_fsm(
        &fsm,
        transition_table,
        sizeof(transition_table) / sizeof(StateTransition),
        init_state,
        NULL
    )) {
        return 1;
    }

    while (1) {
        execute_fsm(&fsm);

        /* Do other stuff. */
    }

    return 0;
}

/* Example implementation of a state function: */
static int wait_state(void *context) {
    /* Do some stuff. */

    if (/* Success condition. */) {
        return 0;
    } else if (/* Timeout condition. */) {
        return 2;
    } else {
        /* Error. */
        return 1;
    }
}

/* ... */
```
