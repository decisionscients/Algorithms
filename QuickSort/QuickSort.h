#pragma once
#include<algorithm>
#include<array>
#include<cmath>
#include<fstream>
#include<iostream>
#include<stdio.h> 
#include<stdlib.h>
#include<vector>

// Returns the index of the pivot, given the pivot rule.
unsigned long int SetPivot(std::vector<unsigned long int>& arr,
	unsigned long int left, unsigned long int right,
	char pivot_rule);

// Partitions an input array A around a pivot
unsigned long int Partition(std::vector<unsigned long int>& arr, 
							unsigned long int left, unsigned long int right,
							char pivot_rule);

// Performs QuickSort recursively 
unsigned long int QuickSort(std::vector<unsigned long int>& arr,
	unsigned long int left, unsigned long int right,
	char pivot_rule);
