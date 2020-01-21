//Creates a structure for integer splits
using namespace std;
#include "SplitInteger.h"


//Splits an integer in half by digits

int main(int x)
{

    struct integer_splits response;
    const unsigned int Base = 10;
    unsigned int divisor = Base;

    while ((x / divisor) > divisor)
    {
        divisor *= Base;
    }
    response.first_half = x / divisor;
    response.second_half = x % divisor;

    return 0;

}