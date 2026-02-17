#include "QuantumState.h"
#include "QuantumGates.h"
#include <iostream>
#include <cmath> // For sqrt
#include <vector>
#include <complex>
#include <random>
// using namespace std;

int main(int argc, char* argv[]){
    // 1. Create a 4 qubit state with random amplitudes
    const int num_qubits = 4;
    const int64_t state_size = 1LL << num_qubits;
    
    std::vector<std::complex<double>> random_amplitudes(state_size);
    double norm_sq_sum = 0.0;

    // Use a random number generator
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Generate random complex numbers and calculate the sum of their squared norms
    for (int64_t i = 0; i < state_size; ++i) {
        random_amplitudes[i] = {dis(gen), dis(gen)};
        norm_sq_sum += std::norm(random_amplitudes[i]);
    }

    // Normalize the amplitudes
    const double norm_factor = std::sqrt(norm_sq_sum);
    for (int64_t i = 0; i < state_size; ++i) {
        random_amplitudes[i] /= norm_factor;
    }

    // Use the custom quantum state builder
    QuantumState qstate(num_qubits, random_amplitudes);
    std::cout << "\nCreated custom random 4-qubit state:" << std::endl;
    qstate.display_sys_state();
    std::cout << "Is Valid? " << (qstate.is_sys_valid() ? "Yes" : "No") << std::endl;

    // 2. Choose target 2, invoke ApplyPhaseflip
    GenericGate gate;
    const int16_t target_qubit = 2;
    std::cout << "\nApplying Phase-flip to qubit " << target_qubit << "..." << std::endl;
    gate.ApplyPhaseflip(&qstate, target_qubit);

    // 3. Print the resulting state
    std::cout << "\nState after Phase-flip:" << std::endl;
    qstate.display_sys_state();
    std::cout << "Is Valid? " << (qstate.is_sys_valid() ? "Yes" : "No") << std::endl;

    return 0;
}