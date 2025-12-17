# QuantumC: Post-Quantum Networking Support Library for C

## 1. Overview

QuantumC is a portable C library that provides post-quantum secure session establishment for networked applications on GNU/Linux and other POSIX systems.

The library is designed to integrate with existing C networking code using standard sockets and event loops. It does not replace TCP, UDP, or application protocols. Instead, it provides a cryptographic session layer that can be embedded into current designs with minimal disruption.

QuantumC targets developers who need post-quantum readiness while maintaining compatibility with existing infrastructure.

---

## 2. Design Goals

* Post-quantum secure key establishment.
* Clean C API with explicit state management.
* Transport-agnostic design.
* No hidden I/O or threading.
* Suitable for long-lived daemons and constrained environments.
* Easy to audit and reason about.

---

## 3. Non-Goals

* Defining a new network protocol.
* Implementing routing or packet forwarding.
* Replacing TLS, IP, or socket APIs.
* Acting as a cryptographic research sandbox.

---

## 4. Architecture

QuantumC is structured as three layers:

### 4.1 Core Session Layer

Responsible for:

* Session lifecycle management.
* Handshake state machines.
* Key derivation orchestration.
* Error handling.

### 4.2 Cryptographic Provider Layer

Responsible for:

* Post-quantum KEM implementations.
* Hybrid classical and post-quantum key exchange.
* Algorithm dispatch via abstract interfaces.

No application code depends directly on algorithm-specific details.

### 4.3 Transport Binding Layer

Provides optional helpers for POSIX sockets. All I/O remains under user control. The library consumes and produces byte buffers only.

---

## 5. Public API Overview

All public interfaces are exposed under `include/quantumc/`.

Key headers include:

* `qc_context.h`; global library configuration.
* `qc_session.h`; session creation and state transitions.
* `qc_crypto.h`; cryptographic configuration.
* `qc_kem.h`; post-quantum KEM abstraction.
* `qc_transport.h`; optional socket helpers.
* `qc_errors.h`; error codes and diagnostics.

The API is designed to be usable in `select()`, `poll()`, and `epoll()` driven applications.

---

## 6. Cryptographic Model

QuantumC supports post-quantum key establishment through a pluggable KEM interface.

### 6.1 Supported Concepts

* Lattice-based KEMs.
* Hybrid classical plus post-quantum handshakes.
* Explicit key material handling.

### 6.2 Algorithm Policy

Algorithms are selected at build or runtime via configuration. No algorithm is hardcoded into the session logic.

This allows users to:

* Track evolving standards.
* Swap implementations without rewriting application code.
* Meet regulatory or organizational requirements.

---

## 7. Build and Integration

### 7.1 Requirements

* C99-compatible compiler.
* POSIX environment.
* Make or compatible build system.

### 7.2 Build

```
make
make install
```

The library builds as a static or shared object depending on configuration.

### 7.3 Integration

QuantumC is intended to be linked directly into applications or system services. No background services or kernel modules are required.

---

## 8. Security Model

* No implicit trust assumptions.
* Explicit handshake transcripts.
* No silent algorithm downgrade.
* Fail-closed behavior.

See `docs/threat_model.md` for details.

---

## 9. Status

This project is under active development. API stability is a priority, but breaking changes may occur prior to the first stable release.

---

## 10. License

GPLv3. See `LICENSE` for details.
