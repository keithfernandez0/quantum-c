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

qc_state_t qc_session_get_state(const qc_session_t *s) {
	if (!s) return QC_STATE_ERROR;
	return s->state;
}

void qc_session_free(qc_session_t *session) {
    	if (session) {
        	free(session->read_buffer);
        	free(session);
    	}
}

// empty versions of functions for now
int qc_session_provide_data(qc_session_t *s, const uint8_t *buf, size_t len) {
	(void)s; (void)buf; (void)len; // suppress unused parameter warnings
	return 0;
}

int qc_session_get_handshake_data(qc_session_t *s, uint8_t *buf, size_t max_len) {
	(void)s; (void)buf; (void)max_len;
	return 0;
}
