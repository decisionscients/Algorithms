#pragma once
#include <vector>
#include<iostream>
#include<fstream>
#include<stdlib.h> 
#include<stdio.h> 

// Counts split inversions.
std::vector<unsigned long int> CountSplitInversions(std::vector<unsigned long int> left,
    std::vector<unsigned long int> right, unsigned long int* num_inv);

// Counts left and right inversions.
std::vector<unsigned long int> CountInversions(std::vector<unsigned long int> arr, unsigned long int* num_inv);

// Reads input file.
bool ReadFile(std::string filename, std::vector<unsigned long int>& arr);