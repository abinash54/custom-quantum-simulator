#include "QuantumState.cpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    QuantumState qstate(2);
    qstate.display_sys_state();
    cout << qstate.is_sys_valid() << endl;

    // initiating gate
    ComplexMatrix2x2 X_Gate;
    X_Gate.m[0][0] = {0.0, 0.0}; X_Gate.m[0][1] = {1.0, 0.0};
    X_Gate.m[1][0] = {1.0, 0.0}; X_Gate.m[1][1] = {0.0, 0.0};

    // cyan applying X gate
    qstate.apply_gate(1, X_Gate);

    qstate.display_sys_state();
    std::cout << "Is Valid? " << (qstate.is_sys_valid() ? "Yes" : "No") << std::endl;

    // cyan applying hadamard gate]
    double coeff_H = 1/sqrt(2);
    ComplexMatrix2x2 H_gate[2][2];

    H_gate[0]

}