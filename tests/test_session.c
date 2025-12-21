#include <stdio.h>
#include <assert.h>
#include "quantumc/qc_session.h"

int main() {
    printf("Testing QuantumC Session Allocation...\n");

    // 1. Create session
    qc_session_t *session = qc_session_create();
    assert(session != NULL);
    printf("[PASS] Session created.\n");

    // 2. Verify initial state
    qc_state_t initial_state = qc_session_get_state(session);
    assert(initial_state == QC_STATE_IDLE);
    printf("[PASS] Initial state is IDLE.\n");

    // 3. Cleanup
    qc_session_free(session);
    printf("[PASS] Session freed.\n");

    printf("\nAll initial verification tests passed!\n");
    return 0;
}
