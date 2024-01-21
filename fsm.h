#ifndef FSM_H
#define FSM_H


#include <stddef.h>


typedef int (*StateFunction)(void *context);


/* Object to define a transition from one state (src_state) to another
 * (dst_state) at the end of execute_fsm. This transition happens only when
 * src_state returns the same value as return_code. */
typedef struct StateTransition {
    StateFunction src_state;
    int return_code;
    StateFunction dest_state;
} StateTransition;

/* The finite state machine object. Holds the machine's current state function,
 * an arbitrary context structure that gets passed between states, and the
 * current state's return code (after execute_fsm is called). The structure
 * stores the machine's transition table, an array of StateTransitions. */
typedef struct FiniteStateMachine {
    StateFunction current_state;
    void *current_state_context;
    int return_code;
    StateTransition *transition_table;
    size_t transition_table_len;
} FiniteStateMachine;


/* Populate a FiniteStateMachine object with its transition table, the length
 * of the table, the machine's initial state function, and context that gets
 * passed between states. The context structure is arbitrary and does not get
 * accessed by the library itself. If NULL, the context will be set to a
 * pointer to the FiniteStateMachine object itself. */
int initialise_fsm(
    FiniteStateMachine *fsm,
    StateTransition transition_table[], size_t n,
    StateFunction initial_state, void *initial_state_context
);

/* Execute the current state function with the context as its argument. On
 * return, change to the next state in accordance to the state function's
 * return value with the transition table. */
void execute_fsm(FiniteStateMachine *fsm);


#endif