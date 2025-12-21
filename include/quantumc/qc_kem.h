#ifndef QUANTUMC_KEM_H
#define QUANTUMC_KEM_H

#include <stddef,h>
#include <stdint.h>

/* declaring skeleton form of KEM (key encapsulation mechanism) */
typedef struct qc_kem_impl qc_kem_impl_t;

/* the KEM interface: every algorithm must provide these functions */
typedef struct {
	const char* name;
	size_t	public_key_kem;
	size_t	ciphertext_len;
	size_t	shared_secret_len;

	/* function pointers for math operations */
	int (*keypair)(uint8_t *pk, uint8_t *sk);
	int (*encaps)(uint8_t *ct, uint8_t *ss, const uint8_t *pk);
	int (*decaps)(uint8_t *ss, const uint8_t *ct, const uint8_t *sk);
} qc_kem_interface_t;

/* this is the object the user or session actually holds */
typedef struct {
	const qc_kem_inteface_t *dispatch;
	uint8_t *public_key;
	uint8_t *secret_key;
} qc_kem_t;

/* helper to initialize KEM based on a specific algorithm */
int qc_kem_init(qc_kem_t *kem, const qc_kem_interface_t *algo);
void qc_kem_cleanup(qc_kem_t *kem);

#endif
