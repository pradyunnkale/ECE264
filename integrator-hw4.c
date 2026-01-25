// ***
// *** You MUST modify this file
// ***
#include <stdio.h>
#include <stdbool.h>
#include "hw4.h"

// must enclose the function by #ifdef TEST_INTEGRATE and #endif
#ifdef TEST_INTEGRATE
void integrate(Integration * intrg)
{
  // integrate the function stored in intrg's func
  // store the result in intrg's answer
	// Trapezoidal Integration (a + b) * interval_size / 2
	int i;
	double prev_y = intrg->func(intrg->lowerlimit);
	double integral = 0.0;
	double interval_size = (intrg->upperlimit - intrg->lowerlimit) / intrg->intervals;

	for (i = 1; i <= intrg->intervals; i++)
	{
		double x = intrg->lowerlimit + i * interval_size;
		double y = intrg->func(x);
		integral += (y + prev_y) * interval_size / 2;
		prev_y = y;	
	}

	intrg->answer = integral;
}
#endif // TEST_INTEGRATE

// must enclose the function by #ifdef RUN_INTEGRATE and #endif
#ifdef RUN_INTEGRATE
bool  runIntegrate(char * infilename, char * outfilename)
// return true if it can successfully open and read the input 
// and open and write the output
// return false when encountering any problem
{
	Integration intrg_struct;
	Integration *intrg = &intrg_struct;
  // open the input file name for reading
	FILE *fp = fopen(infilename, "r");
  // if fopen fails, return false
	if (fp == NULL)
	{
		return false;	
	}
  // read one double from the input file and store it in 
  // intrg's lowerlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
	if (fscanf(fp, "%lf", &(intrg->lowerlimit)) != 1)
	{
		fclose(fp);
		return false;	
	}
  // read one double from the input file and store it in 
  // intrg's upperlimit
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
	if (fscanf(fp, "%lf", &(intrg->upperlimit)) != 1)
	{
		fclose(fp);
		return false;
	}
  // read one int from the input file and store it in 
  // intrg's intervals
  // use fscanf
  // check the return value. If the return value is not one
  // close the file and return false
	if (fscanf(fp, "%d", &(intrg->intervals)) != 1)
	{
		fclose(fp);
		return false;
	}
  // close the input file
	fclose(fp);
  // open the output file for writing
  // if fopen fails, return false
	fp = fopen(outfilename, "w");
	if (fp == NULL)
	{
		return false;	
	}
  // create an array of funcptr called funcs with five elements:
  // func1, func2, ..., func5
	funcptr funcs[5] = {func1, func2, func3, func4, func5};
  // go through the elements in funcs 
  // for each element, call integrate for that function
  // write the result (stored in intrg's answer to 
  // the output file. each answer occupies one line (add "\n")
  // use fprintf
	int i;
	for (i = 0; i < sizeof(funcs) / sizeof(funcptr); i++)
	{
		intrg->func = funcs[i];
		integrate(intrg);
		// check the return value of fprintf. 
		// If it is less one one, close the output
		// file and return false
		if (fprintf(fp, "%f\n", intrg->answer) < 1)
		{
			fclose(fp);
			return false;
		}
	}
  // after going through all functions in funcs
  // close the output file
	fclose(fp);
  // if the function reaches here, return true
	return true;
}
#endif // RUN_INTEGRATE
