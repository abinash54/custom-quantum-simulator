#include "QuantumState.cpp"
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
    QuantumState qstate(14);
    qstate.display_sys_state();
    cout << qstate.is_sys_valid() << endl;

}