#include <iostream>
#include <cstdint>
#include <vector>
#include <complex>
#include <cmath>
// #include <std>


class QuantumState {

    private:
        int64_t num_qubits=0; // will be set after safety check of user input
        std::vector<std::complex<double>> state_vector_space;
        bool q_flag=false;
        int64_t hSpaceSize=1;

        
    public:

        QuantumState(int64_t n_qubit):num_qubits(n_qubit){
            if (n_qubit > 0 && n_qubit <= 30){
                num_qubits = n_qubit;
                // setting vector size
                hSpaceSize = (int64_t)1 << num_qubits;
                state_vector_space.resize(hSpaceSize);
                state_vector_space[0] = {1.0, 0.0};
                return;
            }
            else{
                q_flag=true;
                std::cout << "set some valid qubit number\n";
                return;
            }
        }
        
        void display_sys_state(){
            if(q_flag){
                std::cout << "\ninvalid qubit count" <<"\n";
                return;
            }
            std::cout << "\nsystem qubit count: " << num_qubits << "\n";
            std::cout <<"\nH-Space size: " << hSpaceSize << "\n";
            return;
        }

        bool is_sys_valid(){
            if(q_flag) return false;
            float total_prob = 0;
            for(ulong i=0;i<state_vector_space.size();++i){
                total_prob += std::norm(state_vector_space[i]);
            }

            if (std::abs(total_prob - 1.0) > 1e-9) return false;
            else return true;
        }

};

struct ComplexMatrix2x2{
    std::complex<double> m[2][2];
};