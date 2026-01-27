/* YOU MUST MODIFY THIS FILE */
// Read "hw3.h" to learn about the two data types: `Range` and `RangeAnswer`

#include "hw3.h"

double integrate1(Range rng)
{
  
  /* Fill in for Part 1 */
  // calculate the numerical integration of the function func
  // based on the three attributes (`lowerlimit`, `upperlimit`, and `intervals`) of the type `Range`.
  // the return value of function `integrate1` should be the numerical integration (return type is double)  
	
	double interval_size = (rng.upperlimit - rng.lowerlimit) / rng.intervals;
	double prev_y = func(rng.lowerlimit);
	double sum = 0.0;
	for (int i = 1; i < rng.intervals; i++)
	{
		double x = rng.lowerlimit + i * interval_size;	
		double y = func(x);
		sum += (prev_y + y) * interval_size / 2;
	}
  return sum;
}

void integrate2(RangeAnswer * rngans)
{
  /* Fill in for Part 2 */
  // run `integrate1` function
  // take the return value from `integrate1` function 
  // and assign it to attribute `answer` of the type `RangeAnswer`
	rngans->answer = integrate1(rngans->rng); 
}
