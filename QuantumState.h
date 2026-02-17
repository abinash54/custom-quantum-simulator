#ifndef QUANTUM_STATE_H
#define QUANTUM_STATE_H

#include <cstdint>
#include <vector>
#include <complex>
#include<iostream>

// Forward-declaration to break circular dependency for the 'friend' declaration.
class GenericGate;

struct ComplexMatrix2x2 {
    std::complex<double> m[2][2];
};

class QuantumState {
    // GenericGate methods need to access the internal state vector.
    friend class GenericGate;

private:
    int32_t num_qubits = 0;
    std::vector<std::complex<double>> state_vector_space;
    bool q_flag = false;
    int64_t hSpaceSize = 0;

public:
    // Constructors
    explicit QuantumState(int32_t n_qubit);
    // custom quantum state making
    QuantumState(int64_t n_qubit, const std::vector<std::complex<double>>& input_amplitudes);

    // Member functions
    void display_sys_state() const;
    bool is_sys_valid() const;
    int32_t get_num_qubits() const { return num_qubits; }
    int64_t get_hspace_size() const { return hSpaceSize; }

    void apply_gate(int target_qubit, ComplexMatrix2x2 gate);
};

#endif // QUANTUM_STATE_H