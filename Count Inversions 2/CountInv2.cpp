// Counts the number of inversions in a sequence of unsigned long integers
#include<iostream>
#include<fstream>
#include<stdlib.h> 
#include<stdio.h> 
#include <vector>

std::vector<unsigned long int> CountSplitInversions(std::vector<unsigned long int> left,
    std::vector<unsigned long int> right, unsigned long int* num_inversions) {

    std::vector<unsigned long int> output;
    unsigned long int i = 0, j = 0;

    // Traverse left and right vectors and populate the output vector with 
    // sorted elements of the left and right vectors
    while (i < left.size() && j < right.size()) {

        // If the left value is less than the right, no inversion, move
        // the value to the output vector and increment the index.
        if (left[i] <= right[j])
            output.push_back(left[i++]);

        // Otherwise, move the right value to the output vector and increment
        // the right index. 
        else {
            output.push_back(right[j++]);
            // Now, we must increment the number of inversions.
            // The number of inversions increases by the number of elements
            // remaining in the left vector. Obviously right, since the right 
            // side value is less than all the values on the left.
            *num_inversions += (left.size() - i);
        }
    }

    // The prior loop stops once the end of either of the vectors is reached.
    // Here, we move the remaining elements, from either vector, to output.
    for (; i < left.size(); i++)
        output.push_back(left[i]);

    for (; j < right.size(); j++)
        output.push_back(right[j]);

    return output;
}
    

std::vector<unsigned long int> CountInversions(std::vector<unsigned long int> arr, unsigned long int * num_inversions) {

    // Base case
    if (arr.size() < 2)
        return arr;

    // Recursive case
    std::vector<unsigned long int> left, right, merged;

    unsigned long int middle = arr.size() / 2;

    // Split arr of n unsigned long integers unsigned long into two arrays, 
    // left and right of n/2 unsigned long integers each
    for (unsigned long int i = 0; i < middle; i++)
        left.push_back(arr[i]);

    for (unsigned long int i = middle; i < arr.size(); i++)
        right.push_back(arr[i]);

    left = CountInversions(left, num_inversions);
    right = CountInversions(right, num_inversions);
    merged = CountSplitInversions(left, right, num_inversions);

    return merged;
}

bool ReadFile(std::string filename, std::vector<unsigned long int>& arr) {
    // Open file
    std::ifstream input_file(filename);

    // Check if object is valid
    if (!input_file) {
        std::cerr << "Cannot open file : " << filename << std::endl;
        return false;
    }

    unsigned long int number;
    // Read the file, line-by-line, until EOF
    while (input_file >> number) {
        arr.push_back(number);
    }

    input_file.close();
    return true;
}

unsigned long int main(unsigned long int argc, char* argv[])
{
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    else {
        std::vector<unsigned long int> arr;
        if (ReadFile(argv[1], arr)) {
            unsigned long int n = std::size(arr);
            std::vector<unsigned long int> output;
            std::cout << "\nSize of input: " << n;
            unsigned long int num_inversions = 0;            
            output = CountInversions(arr, &num_inversions);
            std::cout << "\nNumber of Inversions: " << num_inversions;           
        }
        else {
            return 1;
        }
    }
}
