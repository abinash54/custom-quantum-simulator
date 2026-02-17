#include <iostream>
#include <cmath>
#include "QuantumState.h"

// Constructor for a default |0...0> state.
// Using `explicit` prevents unintentional implicit conversions.
QuantumState::QuantumState(int32_t n_qubit) : num_qubits(n_qubit) {
    if (n_qubit <= 0 || n_qubit > 30) { // Max 30 qubits is reasonable for memory.
        q_flag = true;
        std::cerr << "Error: Qubit count must be between 1 and 30." << std::endl;
        return;
    }
    
    hSpaceSize = (int64_t)1 << num_qubits;
    // Using std::vector handles memory allocation and deallocation automatically.
    // This is safer and cleaner than manual `new`/`delete[]`.
    state_vector_space.resize(hSpaceSize, {0.0, 0.0});
    // Initialize to |0...0> state.
    state_vector_space[0] = {1.0, 0.0};
}

// Constructor for a custom state from a vector of amplitudes.
QuantumState::QuantumState(int64_t n_qubit, const std::vector<std::complex<double>>& input_amplitudes)
    : num_qubits(n_qubit) {
    this->hSpaceSize = (int64_t)1 << num_qubits;
    if (this->hSpaceSize != (int64_t)input_amplitudes.size()) {
        q_flag = true;
        std::cerr << "Error: Input amplitude vector size does not match qubit count." << std::endl;
        return;
    }
    // normalization verification
    double total_probability = 0.0;
    for(int64_t i=0;i<this->hSpaceSize;++i){
        total_probability += std::norm(input_amplitudes[i]);
    }
    if(std::abs(total_probability - 1) > 1e-6) {
        std::cout << "invalide amplitudes, probability not summing to 1" << std::endl;
        return;
    }

    // assigning values to actual class container for states
    state_vector_space = input_amplitudes;
    std::cout << "quantum state created successfully" << std::endl;

    return;
    
}

void QuantumState::display_sys_state() const {
    if (q_flag) {
        std::cout << "\nQuantum state is invalid." << std::endl;
        return;
    }
    std::cout << "\n--- System Params ---\n";
    std::cout << "Qubit count: " << num_qubits << "\n";
    std::cout << "Hilbert Space size: " << hSpaceSize << "\n";
    std::cout << "\n--- System State (Amplitudes) ---\n";
    // Display all state amplitudes, including the first one.
    for (int64_t i = 0; i < hSpaceSize; ++i) {
        std::cout << "i: " << i << " -> " << state_vector_space[i] << std::endl;
    }
    std::cout << "\n--- End State ---\n";
}

bool QuantumState::is_sys_valid() const {
    if (q_flag) return false;
    
    double total_prob = 0.0;
    for (const auto& amplitude : state_vector_space) {
        total_prob += std::norm(amplitude); // std::norm is |z|^2
    }

    // Check if the sum of squared magnitudes is close to 1.
    return std::abs(total_prob - 1.0) < 1e-9;
}

// orange this needs to be moved into QuantumGates class
void QuantumState::apply_gate(int target_qubit, ComplexMatrix2x2 gate) {
    if (target_qubit < 0 || target_qubit >= num_qubits) {
        std::cerr << "Error: Target qubit index is out of bounds." << std::endl;
        return;
    }

    const int64_t half_vec_size = hSpaceSize >> 1;
    const int64_t target_mask = (int64_t)1 << target_qubit;

    for (int64_t i = 0; i < half_vec_size; ++i) {
        // This clever mapping algorithm pairs up state indices that differ only at the target_qubit bit.
        // It's more efficient than iterating through all states.
        int64_t low_part = i & (target_mask - 1);
        int64_t high_part = i & ~(target_mask - 1);
        int64_t idx0 = (high_part << 1) | low_part;
        int64_t idx1 = idx0 | target_mask;

        // Cache the amplitudes before overwriting them.
        const std::complex<double> amp0 = state_vector_space[idx0];
        const std::complex<double> amp1 = state_vector_space[idx1];

        // Apply the 2x2 gate matrix to the pair of amplitudes.
        state_vector_space[idx0] = gate.m[0][0] * amp0 + gate.m[0][1] * amp1;
        state_vector_space[idx1] = gate.m[1][0] * amp0 + gate.m[1][1] * amp1;
    }
}
