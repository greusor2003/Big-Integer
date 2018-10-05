#include "BigIntLib.h"
#include <omp.h>

using namespace std;

BigInt factorial(ullint n)
// calculates n!
// max n = BigInt::base - 1;
{
	BigInt A = 1, B = 1;

	assert(n < A.getbase());

	if (n > 1)
	{
		ullint k;		
		ullint r = n % 2;
		ullint m = n / 2;

#pragma omp parallel private(k) num_threads(2) 
{

#pragma omp sections
{			
  #pragma omp section		
		for (k = 0; k < m; k += 2)	
				A *= BigInt(k + 1) *= BigInt(n - k);
#pragma omp section
		for (k = 1; k < m; k += 2)
				B *= BigInt(k + 1) *= BigInt(n - k);
}
}	
		
		A.Kara(B);

		if (r == 1)
		
			A *= BigInt(m + 1);
	}
	return A;
}

BigInt nchoosek(ullint n, ullint k)
// calculates the combinations of k distinct objects chosen from among n < 1000000000
// distinct onjects
{
	if (n < 2 * k)
		return nchoosek(n, n - k);

	ullint m(k / 2);
	ullint s(n - k + 1);
	ullint r(k % 2);

	ullint i(0);

	BigInt A(1), B(1);

	assert(n < A.getbase());

#pragma omp parallel private(i) num_threads(2) 
	{

#pragma omp sections
		{
#pragma omp section		
			for (i = 0; i < m; i += 2)
				A *= BigInt(n - i) *= BigInt(i + s);
#pragma omp section
			for (i = 1; i < m; i += 2)
				B *= BigInt(n - i) *= BigInt(i + s);
		}
	}

	A.Kara(B);

	// sequential top
	// uncomment to use after commenting out the code right above until just past #pragma omp parallel
/*	for (i = 0; i < m; i++)
		A *= BigInt(n - i) *= BigInt(i + s);
*/
	if (r == 1)
		A *= BigInt(m + s);

	BigInt F = factorial(k);

	A /= F; // division stack overflow for n>80000


	return A;
}



