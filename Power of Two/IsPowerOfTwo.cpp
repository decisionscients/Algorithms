//Evaluates whether a number is a power of 2

#include<cmath>
using namespace std;

bool main(int x)
{	
	if (x <= 0)
	{
		return false;
	}
	return (ceil(log2(x)) == floor(log2(x)));
}