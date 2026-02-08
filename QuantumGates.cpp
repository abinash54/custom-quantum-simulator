#include <iostream>
#include <cmath>
#include <cstdint>
#include <vector>
#include <complex>
#include "QuantumState.cpp"

// forward declaration for fetching num_qubits
class QuantumState{
    public:
        virtual int32_t get_num_qubits() = 0;
};

class GenericGate{
    public:
        int32_t gate_size = 0; // actually number of qubits, will be called in constructor to set
        std::complex<double>* gate_matrix = NULL; // linear array for efficiency
        
        GenericGate(QuantumState* provider){
            gate_size = 1 << provider->get_num_qubits();
            // memory allocation to gate
            gate_matrix = new std::complex<double>[gate_size];

        }

        // destructor
        ~GenericGate(){
            if(gate_matrix != NULL){
                delete[] gate_matrix;
                gate_matrix = NULL;
                return;
            }
            else std::cout << "problem in freeing the gate matrix memory" << std::endl;
        }

        static GenericGate CreateX();
        static GenericGate CreateH();
        static GenericGate CreateCNOT();
        static GenericGate CreateCustom(int n, std::vector<std::complex<double>> data);

        static GenericGate CreateCNOT(QuantumState* qstate){
            
        }
};