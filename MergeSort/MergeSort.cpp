// Merges two arrays of n distinct integers
#include<iostream>
#include<stdlib.h> 
#include<stdio.h> 
#include <vector>

// Merges two subarrays; the first array[l..m]; the second array[m+1..r]
int * Merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // create temp arrays 
    std::vector<int> L;
    std::vector<int> R;

    /* Copy data to temp arrays L[] and R[] */
    for (i = 0; i < n1; i++)
        L.push_back(arr[l + i]);
    for (j = 0; j < n2; j++)
        R.push_back(arr[m + 1 + j]);

    i = 0; // Initial index of first subarray 
    j = 0; // Initial index of second subarray 
    k = l; // Initial index of merged subarray 
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[], if there are any 
    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[], if there are any 
    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }

    return arr;
}





// Implements MergeSort algorithm on an array of n distinct integers
int * MergeSort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;

        // Sort first and second halves 
        arr = MergeSort(arr, l, m);
        arr = MergeSort(arr, m + 1, r);

        arr = Merge(arr, l, m, r);
    }
    return arr;
}

int main_mergesort()
{
    const int n = 8;
    int arr[n] = { 9, 8, 7, 6, 4, 5, 3, 1 };
    int *sorted_array;
    std::cout << "Array before Sorting: ";
    for (int i = 0; i < n; i++)
        std::cout << arr[i];
    sorted_array = MergeSort(arr, 0, std::size(arr) - 1);
    std::cout << "\nArray after Sorting: ";
    for (int i = 0; i < n; i++)
        std::cout << sorted_array[i];
    return 0;    
}
	