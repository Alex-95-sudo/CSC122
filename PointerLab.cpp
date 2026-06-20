#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    srand(time(0)); // Seed random numbers for tasks below

   // Assignment and Dereference

    int a, b;
    cout << "Enter two integers (separated by space): ";
    cin >> a >> b;

    int* ptr_a = &a;
    int* ptr_b = &b;

    cout << "Value via ptr_a: " << *ptr_a << endl;
    cout << "Value via ptr_b: " << *ptr_b << endl << endl;


   //Max in Array 

    int nums[8];
    cout << "Generated array: ";
    for (int i = 0; i < 8; i++) {
        *(nums + i) = rand() % 100 + 1; // standard pointer offset notation
        cout << *(nums + i) << " ";
    }
    cout << endl;

    int* max_ptr = nums; 
    int* current = nums + 1;
    int* end_ptr = nums + 8;

    // Linear search checking values rather than addresses
    while (current < end_ptr) {
        if (*current > *max_ptr) {
            max_ptr = current;
        }
        current++;
    }
    cout << "Max value found: " << *max_ptr << endl << endl;


    //Length of C-Style String

    char str[] = "Helloworld";
    char* str_ptr = str;
    int cells_visited = 0;

    while (*str_ptr != '\0') {
        cells_visited++;
        str_ptr++; // shifts to next character block
    }
    cout << "String: " << str << endl;
    cout << "Cells visited (length): " << cells_visited << endl << endl;


//Reverse C-Style String

    char rev_str[] = "ComputerScience";
    char* p_rev = rev_str;

    cout << "Original: " << rev_str << endl;
    cout << "Reversed: ";
    
    // push pointer to the null terminator edge
    while (*p_rev != '\0') {
        p_rev++;
    }

    // back up one step so we aren't printing the null terminator itself
    p_rev--; 

    // loop backwards until we pass the original array starting bound
    while (p_rev >= rev_str) {
        cout << *p_rev;
        p_rev--;
    }
    cout << endl << endl;


  //Midpoit of Vector

    // Creating a vector with an odd size to test direct meeting point
    vector<int> vec = {10, 24, 35, 42, 57, 61, 79}; 
    
    // Safety check for empty vectors
    if (!vec.empty()) {
        int* start = &vec[0];
        int* end = &vec[vec.size() - 1];

        // step pointers inwards
        while (start < end) {
            start++;
            end--;
        }

        // If even size, 'start' and 'end' cross, 'end' will hold the lower index
        if (start > end) {
            cout << "Midpoint value (even split adjustment): " << *end << endl;
        } else {
            cout << "Midpoint value (exact center match): " << *start << endl;
        }
    }

    return 0;
}