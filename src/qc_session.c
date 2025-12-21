#include "quantumc/qc_session.h"
#include <stdlib.h>

struct qc_session {
    qc_state_t state;
    uint8_t   *read_buffer;
    size_t     buffer_size;
    // internal PQC keys would go here later
};

qc_session_t* qc_session_create(void) {
    qc_session_t *s = malloc(sizeof(struct qc_session));
    if (!s) return NULL;
    
    s->state = QC_STATE_IDLE;
    s->read_buffer = NULL;
    s->buffer_size = 0;
    return s;
}

void qc_session_free(qc_session_t *session) {
    if (session) {
        free(session->read_buffer);
        free(session);
    }
}
