#include <iostream>

int fibonacci(int n) {
    // track number of times function is called
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

    // displays call count 
    std::cout << "Call count updated to: " << total_calls << "\n";

    // calculates current Fibonacci number by adding previous two 
    return fibonacci(n - 1) + fibonacci(n - 2);
}


// New loop-based Fibonacci function
int fibonacciLoop(int n) {
    // Fibonacci values for 0 and negative numbers are treated as 0.
    if (n <= 0) {
        return 0;
    }

    // The first Fibonacci number is 1.
    if (n == 1) {
        return 1;
    }

    // Start with the first two Fibonacci numbers
    int previous = 0;
    int current = 1;

    // Build the Fibonacci sequence from lower numbers up to n
    for (int i = 2; i <= n; i++) {
        int next = previous + current;
        previous = current;
        current = next;
    }

    return current;
}


int main() {
    // Chooses which Fibonacci position to calculate
    int target = 6;

    // Stores the result returned by the recursive function
    int recursiveResult = fibonacci(target);

    // Stores the result returned by the loop function
    int loopResult = fibonacciLoop(target);

    // Prints recursive Fibonacci answer
    std::cout << "\nRecursive Fibonacci number at index " << target
              << " is: " << recursiveResult << "\n";

    // Prints loop Fibonacci answer
    std::cout << "Loop Fibonacci number at index " << target
              << " is: " << loopResult << "\n";

    return 0;
}
