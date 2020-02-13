// Performs randomized QuickSort algorithm and returns number of comparisons
#include<algorithm>
#include<array>
#include<cmath>
#include<fstream>
#include<iostream>
#include<stdio.h> 
#include<stdlib.h>
#include<string>
#include<vector>
using namespace std;

void PrintVec(std::vector<long int>& arr, long int left, long int right, string msg) {
    std::cout << msg;
    for (unsigned int i = left; i < right+1; i++)
        std::cout << arr.at(i) << ' ';
}

void Swap(std::vector<long int>& arr,
    long int idx1, long int idx2) {
    int temp = arr[idx1];
    arr[idx1] = arr[idx2];
    arr[idx2] = temp;
    return;
}

// Return median of value an array
void SetMedian(std::vector<long int>& arr,
    long int left, long int right) {

    long int mid = 0;
    long int length;
    const int n = 3;
        

    // Gets middle value based upon odd or even length
    length = right + 1 - left;
    if (length % 2 == 0)
        mid = left + ((length / 2) - 1);
    else
        mid = left + (length / long int(2));

      
    // Create array containing left, right, and median
    std::array<long int, n> lmr = { arr[left], arr[mid], arr[right] };

    /* Print sorted 3 medians
    std::cout << "  \nLeft : " << lmr[0];    
    std::cout << "  Right : " << lmr[2];
    std::cout << "  Middle : " << lmr[1];
    */
    
    // Sort the array
    std::sort(lmr.begin(), lmr.end());
    
    /* Print median value
    std::cout << "  Median: " << lmr[1];
    */    
    
    // Evaluate whether a swap is needed based upon the index of medians array
    if (lmr[1] == arr[mid])
        Swap(arr, left, mid);
    else if (lmr[1] == arr[right])
        Swap(arr, left, right);
    return;
}

// Returns the pivot for a given pivot rule
void SetPivot(std::vector<long int>& arr,
    long int left, long int right,
    char pivot_rule) {
    
    if (pivot_rule == 'r')
        Swap(arr, left, right);
    else if (pivot_rule == 'm')
        SetMedian(arr, left, right);
    return;
}


long int Partition(std::vector<long int>& arr,
    long int left, long int right,
    char pivot_rule) {

    long int p = arr[left];
    long int i = left + 1;
    for (long int j = left + 1; j <= right; j++)
        if (arr[j] < p) {
            Swap(arr, j, i);
            i = i + 1;
        }
    Swap(arr, left, i - 1);
    return i - 1;
}

void QuickSort(std::vector<long int>& arr,
    long int left, long int right,
    char pivot_rule, long int * num_comparisons) {
    
    long int j = 0;
    long int m = right - left + 1;
    string msg;

    if (left >= right)
        return;

    //msg = "\n\nInput array: ";
    //PrintVec(arr, left, right, msg);
    SetPivot(arr, left, right, pivot_rule);

    j = Partition(arr, left, right, pivot_rule); // partition & set pivot first
    
    *num_comparisons = *num_comparisons + m - 1;
    //std::cout << " Count = " << m-1;
    
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
            QuickSort(arr, 0, (m - 1), 'm', &num_comparisons);            
            std::cout << "\n\nNumber of comparisons: " << num_comparisons;

            return 0;
        }
        else
        {
            return 1;
        }
    }
}