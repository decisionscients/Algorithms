// Performs randomized QuickSort algorithm and returns number of comparisons
#include<algorithm>
#include<array>
#include<cmath>
#include<fstream>
#include<iostream>
#include<stdio.h> 
#include<stdlib.h>
#include<vector>
using namespace std;

std::vector<long int> Swap(std::vector<long int>& arr,
    long int idx1, long int idx2) {
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
    return arr;
}

// Return median of value an array
std::vector<long int> SetMedian(std::vector<long int>& arr,
    long int left, long int right) {

    long int mid = 0;
    long int length;
    const int n = 3;
        

    // Gets middle value based upon odd or even length
    length = right + 1 - left;
    if (length % 2 == 0)
        mid = (length / 2) - 1;
    else
        mid = length / long int(2);

      
    // Create array containing left, right, and median
    std::array<long int, n> lrm = { arr[left], arr[mid], arr[right] };

    // Sort the array
    std::sort(lrm.begin(), lrm.end());
        
    // Evaluate whether a swap is needed based upon the index of medians array
    if (lrm[1] == arr[mid])
        arr = Swap(arr, left, mid);
    else if (lrm[1] == arr[right])
        arr = Swap(arr, left, right);
    return arr;
}

// Returns the pivot for a given pivot rule
std::vector<long int> SetPivot(std::vector<long int>& arr,
    long int left, long int right,
    char pivot_rule) {
    
    if (pivot_rule == 'r')
        arr = Swap(arr, left, right);
    else if (pivot_rule == 'm')
        arr = SetMedian(arr, left, right);
    return arr;
}


long int Partition(std::vector<long int>& arr,
    long int left, long int right,
    char pivot_rule) {
    
    arr = SetPivot(arr, left, right, pivot_rule);
    long int p = arr[left];
    long int i = left + 1;
    for (long int j = left + 1; j <= right; j++)
        if (arr[j] < p) {
            arr = Swap(arr, j, i);
            i = i + 1;
        }
    arr = Swap(arr, left, i - 1);
    return i - 1;
}

void QuickSort(std::vector<long int>& arr,
    long int left, long int right,
    char pivot_rule, long int * num_comparisons) {
    
    long int j = 0;
    long int m = right - left + 1;

    if (left >= right)
        return;
    j = Partition(arr, left, right, pivot_rule); // partition & set pivot first

    *num_comparisons = *num_comparisons + m - 1;
    
    QuickSort(arr, left, j - 1, pivot_rule, num_comparisons);        // recurse on first part.
    QuickSort(arr, j + 1, right, pivot_rule, num_comparisons);       // recurse on second part.    
    return;
}


bool ReadFile(std::string filename, std::vector<long int>& arr)
{
    // Open file
    std::ifstream input_file(filename);

    // Check if objet is valid
    if (!input_file)
    {
        std::cerr << "Cannot open file : " << filename << std::endl;
        return false;
    }

    long int number;
    // Read the file, line-by-line, until EOF
    while (input_file >> number)
    {
        arr.push_back(number);
    }

    input_file.close();
    return true;
}

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>\n";
        return 1;
    }
    else
    {
        std::vector<long int> arr;
        if (ReadFile(argv[1], arr))
        {
            long int m = std::size(arr);            
            long int num_comparisons = 0;

            std::cout << "\nSize of input: " << m;
            std::cout << "\nUnsorted Array: ";
            for (auto i = arr.begin(); i != arr.end(); ++i)
                cout << *i << " ";
            
            QuickSort(arr, 0, (m - 1), 'r', &num_comparisons);
            
            std::cout << "\n\nNumber of Comparisons: " << num_comparisons;
            std::cout << "\nSorted Array: ";
            for (auto i = arr.begin(); i != arr.end(); ++i)
                cout << *i << " ";
            return 0;
        }
        else
        {
            return 1;
        }
    }
}