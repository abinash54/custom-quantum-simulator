The Challenge: The QuantumState Class
Goal: Create the "memory" of your quantum computer.

<The Task>:Create a C++ class named QuantumState.
Constructor: It should accept num_qubits (an integer) and allocate a vector of size $2^{\text{num\_qubits}}$.
    Math Note: The system starts in the "Ground State" $|00...0\rangle$. This means the first element (index 0) is 1.0 + 0i, and all other elements are 0.0 + 0i.

Utility: Implement a method print_state() that prints the amplitude of every basis state.

Technical Constraints:

Language: C++ (Standard C++17 or C++20 recommended).

Data Type: Use std::vector<std::complex<double>>. This is the standard for high-precision scientific computing.

Efficiency: Using std::pow to calculate the vector size is slow and returns a float. Use bit-shifting (1 << n) to calculate powers of 2 for integer sizes.