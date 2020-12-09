#ifndef N64_DEBUGGER_TYPES
#define N64_DEBUGGER_TYPES

#ifndef N64_WIN
#include <gdbstub.h>
#endif

typedef struct n64_breakpoint n64_breakpoint_t;

typedef struct n64_breakpoint {
#ifndef N64_WIN
    word address;
    n64_breakpoint_t* next;
#endif
} n64_breakpoint_t;

typedef struct n64_debugger_state {
#ifndef N64_WIN
    gdbstub_t* gdb;
    bool broken;
    int steps;
    n64_breakpoint_t* breakpoints;
    bool enabled;
#endif
} n64_debugger_state_t;

INLINE bool check_breakpoint(n64_debugger_state_t* state, word address) {
#ifndef N64_WIN
    n64_breakpoint_t* cur = state->breakpoints;
    while (cur != NULL) {
        if (cur->address == address) {
            return true;
        }
        cur = cur->next;
    }
    return false;
#endif
}
#endif
