#include<iostream>
using namespace std;

void apply_gate(int target_qubit){
    int vec_sz = 1 << 5;
    cout<< "space size: " << vec_sz << endl;
    vec_sz = vec_sz >> 1;
    for (int i=0;i<vec_sz;++i){
        // creating low mask
        long l_mask = (long)(1 << target_qubit) - 1;
        long h_mask = (long)(i >> target_qubit) << (target_qubit+1);
        // processing the loop count value to create a zero at position target_qubit
        long l_segment = i & l_mask;
        // h_mask stay the same since its already cleaned where left to target_qubit are 1, including
        // finding indexes
        int idx0 = l_segment | h_mask;
        int idx1 = idx0 | (1 << target_qubit);
        cout << "i: " << i;
        cout << "\tlmask: " << l_mask << ", hmask: " << h_mask << endl;
        cout << "\tidx0: " << idx0 << ", idx1: " << idx1 << endl;
    }
}

int main(){
    apply_gate(2);
}