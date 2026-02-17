#include "QuantumGates.h"
#include <utility> // For std::swap

void GenericGate::ApplyCNOT(QuantumState* qstate, int16_t q_target, int16_t q_control) {
    // Validate qubit indices to prevent errors.
    if (!qstate || q_target < 0 || q_control < 0 ||
        q_target >= qstate->get_num_qubits() || q_control >= qstate->get_num_qubits() ||
        q_target == q_control) {
        // Consider throwing an exception or logging an error for better handling.
        return;
    }
    
    // Use int64_t for masks and sizes to match hSpaceSize and avoid overflow
    // for larger qubit systems.
    const int64_t ctrl_mask = (int64_t)1 << q_control;
    const int64_t target_mask = (int64_t)1 << q_target;
    const int64_t q_vectorSize = qstate->get_hspace_size();
    
    // Iterate through all basis states.
    for (int64_t i = 0; i < q_vectorSize; ++i) {
        // Check if the control bit is set in the current basis state 'i'.
        // The `(i & ctrl_mask) != 0` is a more explicit check than just `(i & ctrl_mask)`.
        if ((i & ctrl_mask) != 0) {
            // To avoid swapping twice, we only perform the swap when the target bit is 0.
            // The state `i` has control=1, target=0.
            // The state `idxB` will have control=1, target=1.
            if ((i & target_mask) == 0) {
                int64_t idxB = i | target_mask; // The state with the target bit flipped to 1.
                // The 'friend' declaration in QuantumState.h allows this access to private members.
                std::swap(qstate->state_vector_space[i], qstate->state_vector_space[idxB]);
            }
        }
    }
}

void GenericGate::ApplyPhaseflip(QuantumState* qstate, int16_t q_target){
    // validation
    if(q_target < 0){
        std::cout << "invalid target qubit" << std::endl;
    }
    // generating the mask, qubit count is from right, starting zero
    int32_t zMask = 1 << q_target;
    // linear searching for location aka states where target location  has 1 in it bit
    int64_t state_size = qstate->hSpaceSize;
    for(int64_t i=0;i<state_size;++i){
        if(i & zMask) qstate->state_vector_space[i] = -1.0 * qstate->state_vector_space[i];
    }

    std::cout << "Phase flip operation completed successfully" << std::endl; 
}