// Counts the number of inversions in a sequence of integers
#include<iostream>
#include<fstream>
#include<stdlib.h> 
#include<stdio.h> 
#include <vector>

// Declarations
unsigned long int CountInversions(std::vector<unsigned long int>& arr, std::vector<unsigned long int>& temp, 
                    unsigned long int left, unsigned long int right);
unsigned long int CountSplitInversions(std::vector<unsigned long int>& arr, std::vector<unsigned long int>& temp, 
                         unsigned long int left, unsigned long int mid, 
                         unsigned long int right);

// Function that recursively counts inversions using divide/conquer approach.
unsigned long int CountInversions(std::vector<unsigned long int>& arr, 
                    std::vector<unsigned long int>& temp,
                    unsigned long int left, unsigned long int right)
{
    unsigned long int mid = 0;
    unsigned long int num_inv = 0;

    /* create temp arrays */
    if (right > left)
    {
        // Split the array in half
        mid = (left + right) / 2;

        // Call CountInversions on each half
        num_inv += CountInversions(arr, temp, left, mid);
        num_inv += CountInversions(arr, temp, mid + 1, right);

        // Merge left and right parts and count split inversions
        num_inv += CountSplitInversions(arr, temp, left, mid + 1, right);
    }

    return num_inv;
}
    
// Counts the number of split inversions in two arrays of n distinct integers
unsigned long int CountSplitInversions(std::vector<unsigned long int>& arr, 
                                       std::vector<unsigned long int>& temp,
                                       unsigned long int left, unsigned long int mid, 
                                       unsigned long int right)
{    
    unsigned long int i = left;
    unsigned long int j = mid;
    unsigned long int k = left;

    unsigned long int num_inv = 0;
    while ((i <= (mid - 1)) && (j <= right))
    {
        if (arr[i] <= arr[j])
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
            num_inv = num_inv + (mid - i + 1);
        }
    }
    // Copy remaining elements of left to temp
    while (i <= (mid - 1))    
        temp[k++] = arr[i++];
    
    // Copy remaining elements of right to temp
    while (j <= right)    
        temp[k++] = arr[j++];
    
    // Copy (sorted and ) merged elements back to original array
    for (i = left; i <= right; i++)
    {
        arr[i] = temp[i];
    }
    return num_inv;
}

bool ReadFile(std::string filename, std::vector<unsigned long int>& arr)
{
    // Open file
    std::ifstream input_file(filename);

    // Check if objet is valid
    if (!input_file)
    {
        std::cerr << "Cannot open file : " << filename << std::endl;
        return false;
    }

    unsigned long int number;
    // Read the file, line-by-line, until EOF
    while (input_file >> number)
    {
        arr.push_back(number);
    }

    input_file.close();
    return true;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    else
    {
        std::vector<unsigned long int> arr;
        if (ReadFile(argv[1], arr))
        {
            unsigned long int n = std::size(arr);
            std::cout << "\nSize of input: " << n;
            unsigned long int num_inversions = 0;
            std::vector<unsigned long int> temp(n, 0);
            num_inversions = CountInversions(arr, temp, 0, (n - 1));
            std::cout << "\nNumber of Inversions: " << num_inversions;
        }
        else
        {
            return 1;
        }
    }
}
