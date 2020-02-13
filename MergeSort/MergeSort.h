#pragma once
#include<iostream>
#include<stdlib.h> 
#include<stdio.h> 
#include <vector>

// Merges two subarrays; the first array[l..m]; the second array[m+1..r]
int* Merge(int arr[], int l, int m, int r);

// Implements MergeSort algorithm on an array of n distinct integers
int* MergeSort(int arr[], int l, int r);
