# QuantumC Threat Model

## 1. Scope

This document defines the threat model for QuantumC, a C library providing post-quantum secure session establishment for networked applications.

QuantumC operates strictly in user space and does not modify or replace underlying transport protocols. The threat model applies to the cryptographic session layer only.

Out-of-scope components include:
- Operating system security.
- Kernel networking stacks.
- Application-level protocol semantics.
- Physical security of hosts.
- Side-channel resistance beyond software-level mitigations.

---

## 2. Assets

The primary assets protected by QuantumC are:

- Session key material.
- Handshake transcripts.
- Cryptographic context state.
- Peer authentication material, if enabled.

Secondary assets include:
- Algorithm negotiation integrity.
- Forward secrecy of established sessions.
- Resistance to downgrade and replay attacks.

---

## 3. Adversary Model

QuantumC assumes a strong network adversary with the following capabilities:

- Full control over the network channel.
- Ability to observe, inject, modify, replay, and drop packets.
- Long-term storage of captured traffic for future cryptanalysis.
- Access to large-scale classical computing resources.
- Eventual access to large-scale quantum computing resources.

The adversary is assumed **not** to:
- Compromise the host operating system at runtime.
- Read process memory directly.
- Modify the QuantumC binary or headers at build time.
- Break standard cryptographic assumptions outside known threat models.

---

## 4. Security Goals

QuantumC aims to provide the following guarantees:

### 4.1 Confidentiality
Session keys established using post-quantum or hybrid key exchange must remain confidential against both classical and quantum adversaries, subject to the security properties of the selected algorithms.

### 4.2 Integrity
Handshake messages must be protected against undetected modification.

### 4.3 Authentication
When authentication mechanisms are enabled, QuantumC must prevent undetected impersonation of peers.

### 4.4 Forward Secrecy
Compromise of long-term keys must not compromise past session keys.

### 4.5 Downgrade Resistance
An active adversary must not be able to force negotiation of weaker algorithms without detection.

---

## 5. Non-Goals

QuantumC explicitly does not attempt to defend against:

- Compromised endpoints.
- Malicious or vulnerable application logic.
- Side-channel attacks such as cache timing, power analysis, or EM leakage.
- Denial-of-service attacks at the transport or network layer.
- Traffic analysis and metadata leakage inherent to underlying transports.

---

## 6. Trust Assumptions

QuantumC relies on the following assumptions:

- The compiler toolchain is trusted.
- The operating system enforces process isolation.
- Random number generation is cryptographically secure and correctly seeded.
- Linked cryptographic primitives are correctly implemented.

If external cryptographic libraries are used, their correctness and security are transitively trusted.

---

## 7. Cryptographic Assumptions

QuantumC’s post-quantum security relies on hardness assumptions associated with lattice-based cryptography and related constructions.

Hybrid handshakes assume:
- At least one of the combined key exchange mechanisms remains secure.
- Classical and post-quantum failures are independent.

No claim is made regarding resistance to future cryptanalytic breakthroughs beyond current academic understanding.

---

## 8. Handshake and State Machine Threats

The following attack classes are explicitly considered:

- Replay of handshake messages.
- Transcript truncation or reordering.
- Algorithm substitution.
- State desynchronization attacks.

QuantumC mitigates these through:
- Explicit handshake state machines.
- Transcript binding.
- Deterministic error handling.
- Fail-closed behavior on unexpected state transitions.

---

## 9. Memory Safety Considerations

QuantumC is written in C and therefore subject to memory safety risks inherent to the language.

Mitigations include:
- No global mutable state.
- Explicit ownership rules.
- Bounded buffer operations.
- Consistent error propagation.

QuantumC does not claim to be memory-safe in the language-theoretic sense.

---

## 10. Residual Risk

Even with correct implementation and configuration, residual risks remain:

- Cryptographic primitives may be weakened by future research.
- Implementation bugs may introduce vulnerabilities.
- Side-channel leakage may occur on certain platforms.
- Misuse of the API may undermine security guarantees.

Users are expected to conduct independent security reviews appropriate to their deployment environment.

---

## 11. Summary

QuantumC provides a narrowly scoped, auditable foundation for post-quantum secure session establishment in C networking applications. It assumes a powerful adversary and aims to minimize attack surface while remaining practical for real-world deployment.

Security is a process, not a property. This threat model will evolve alongside cryptographic standards and implementation experience.
