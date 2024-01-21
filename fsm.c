#include "fsm.h"

#include <stddef.h>


int initialise_fsm(
    FiniteStateMachine *fsm,
    StateTransition transition_table[], size_t n,
    StateFunction initial_state, void *initial_state_context
) {
    if (!fsm || !transition_table || !initial_state) {
        return 1;
    }

    fsm->current_state = initial_state;
    fsm->current_state_context = initial_state_context ? initial_state_context : fsm;

    fsm->transition_table = transition_table;
    fsm->transition_table_len = n;

    return 0;
}


void execute_fsm(FiniteStateMachine *fsm) {
    fsm->return_code = fsm->current_state(fsm->current_state_context);

    for (size_t i = 0; i < fsm->transition_table_len; ++i) {
        StateTransition transition = fsm->transition_table[i];

        if (fsm->current_state == transition.src_state && fsm->return_code == transition.return_code) {
            fsm->current_state = transition.dest_state;
            break;
        }
    }
}