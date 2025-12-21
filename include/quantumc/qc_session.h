#ifndef QUANTUMC_SESSION_H
#define QUANTUMC_SESSION_H

#include <stddef.h>
#include <stdint.h>

/* The user can see this exists, but they don't know what's in it. */
typedef struct qc_session qc_session_t;

/* State transitions for the handshake */
typedef enum {
    QC_STATE_IDLE,
    QC_STATE_NEGOTIATING,
    QC_STATE_ESTABLISHED,
    QC_STATE_ERROR
} qc_state_t;

/* Lifecycle Management */
qc_session_t* qc_session_create(void);
void          qc_session_free(qc_session_t *session);

/* The "Transport-Agnostic" Engine: 
 * The user feeds bytes from the network into the library. */
int qc_session_provide_data(qc_session_t *s, const uint8_t *buf, size_t len);

/* The library gives bytes back to the user to send over the network. */
int qc_session_get_handshake_data(qc_session_t *s, uint8_t *buf, size_t max_len);

qc_state_t    qc_session_get_state(const qc_session_t *s);

#endif
