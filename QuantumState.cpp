#include <iostream>
#include <cstdint>
#include <vector>
#include <complex>
#include <cmath>
// #include <std>


struct ComplexMatrix2x2{
    std::complex<double> m[2][2];
};

class QuantumState {

    private:
        // yellow qubits in sys
        int32_t num_qubits=0;
        // yellow state container vector  base address
        std::complex<double>* state_vector_space = NULL;
        bool q_flag=false;
        int64_t hSpaceSize=1;

        
    public:

        QuantumState(int64_t n_qubit):num_qubits(n_qubit){
            if (n_qubit > 0 && n_qubit <= 30){
                num_qubits = n_qubit;
                // setting vector size
                hSpaceSize = (int64_t)1 << num_qubits;
                // allocating memory to state space
                state_vector_space = new std::complex<double>[hSpaceSize];
                // initiating all state probabities to 0 except first qubit
                state_vector_space[0] = {1.0, 0.0};
                for (int64_t i=1; i<hSpaceSize; ++i){
                    state_vector_space[i] = {0.0, 0.0};
                }

                return;
            }
            else{
                q_flag=true;
                std::cout << "set some valid qubit number\n";
                return;
            }
        }

        // free memory
        ~QuantumState(){
            if(state_vector_space != NULL){
                delete[] state_vector_space;
                state_vector_space = NULL;
                return;
            }
            else std::cout << "problem in freeing the qubit state space memory" << std::endl;
        }
        
        void display_sys_state(){
            

            if(q_flag | hSpaceSize == 1){
                std::cout << "\ninvalid qubit count or state space size, check if QuantumState class initiated or valid qubit number is given" <<"\n";
                return;
            }
            std::cout << "\n--- System params ---\n";
            std::cout << "\nsystem qubit count: " << num_qubits << "\n";
            std::cout <<"\nH-Space size: " << hSpaceSize << "\n";
            std::cout << "\n--- System State ---\n";
            // showing qubit values
            for (int64_t i=1; i<hSpaceSize; ++i){
                    std::cout << "i: " << i << state_vector_space[i] << std::endl;
            }
            std::cout << "\n--- endl ---\n";

            return;
        }

        bool is_sys_valid(){
            if(q_flag | hSpaceSize == 1) return false;
            double total_prob = 0;
            for(ulong i=0;i<hSpaceSize;++i){
                total_prob += std::norm(state_vector_space[i]);
            }

            if (std::abs(total_prob - 1.0) > 1e-9) return false;
            else return true;
        }

        int32_t get_num_qubits(){
            return num_qubits;
        }

        void apply_gate(int target_qubit, ComplexMatrix2x2 gate){
            long half_vec_size = hSpaceSize >> 1;
            for (int i=0;i<half_vec_size;++i){
                // creating low mask
                long l_mask = (long)(1 << target_qubit) - 1;
                long h_mask = (long)(i >> target_qubit) << (target_qubit+1);
                // processing the loop count value to create a zero at position target_qubit
                long l_segment = i & l_mask;
                // h_mask stay the same since its already cleaned where left to target_qubit are 1, including
                // finding indexes
                int idx0 = l_segment | h_mask;
                int idx1 = idx0 | (1 << target_qubit);

                // extracting complex values
                std::complex<double> idx0_val = state_vector_space[idx0];
                std::complex<double> idx1_val = state_vector_space[idx1];

                state_vector_space[idx0] = gate.m[0][0] *idx0_val + gate.m[0][1] * idx1_val;
                state_vector_space[idx1] = gate.m[1][0] *idx0_val + gate.m[1][1] * idx1_val;
            }

            return;
        }

};
