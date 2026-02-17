#ifndef QUANTUM_GATES_H
#define QUANTUM_GATES_H

#include <cstdint>
#include <vector>
#include <complex>
#include<iostream>

// We need the full definition of QuantumState for the ApplyCNOT method.
#include "QuantumState.h"

class GenericGate {
public:

    // CNOT gate implementor, takes in quantum state vector, O(N) implementation
    // Control and target qubit position counting from right (0-indexed)
    void ApplyCNOT(QuantumState* qstate, int16_t q_target, int16_t q_control);

    // gate for z-operation, linear
    void ApplyPhaseflip(QuantumState* qstate, int16_t q_target);

    // gate for bit-flip ops, linear
    void ApplyBitflip(QuantumState* qstate);

    // hadamard gate
    void ApplyHadamard();
};

#endif // QUANTUM_GATES_H