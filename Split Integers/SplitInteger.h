#pragma once
// Structure used when splitting integers 
struct integer_splits
{
    unsigned int first_half;
    unsigned int second_half;
};
struct integer_splits SplitInteger(int x);
