#include <iostream>

int fibonacci(int n) {
    //track number of time function is called
    static int total_calls = 0;
    total_calls++;

    // Fibonacci values for 0 and negative numbers are treated as 0.
    if (n <= 0) {
        return 0;
    }

    // The first Fibonacci number is 1.
    if (n == 1) {
        return 1;
    }

   //displays call count 
    std::cout << "Call count updated to: " << total_calls << "\n";

    //calculates current Fibonacci number by adding previous two 
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int main() {
    // Chooses which Fibonacci position to calculate
    int target = 6;

    // Stores the result returned by the function
    int result = fibonacci(target);

    // Prints final answer
    std::cout << "\nFibonacci number at index " << target
              << " is: " << result << "\n";

    return 0;
}