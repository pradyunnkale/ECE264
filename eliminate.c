/* You MUST modify this file */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h> 
#include <string.h> 

#ifdef TEST_ELIMINATE
// 100% of the score
void eliminate(int n, int k)
{
  // allocate an arry of n elements
  int * arr = malloc(sizeof(* arr) * n);
  // check whether memory allocation succeeds.
  // if allocation fails, stop
  if (arr == NULL)
    {
      fprintf(stderr, "malloc fail\n");
      return;
    }
	
  // Note that from here on, you can access elements of the arr with
  // expressions like a[i]
	
  // initialize all elements

  int init;
  init = 0;
  while (init < n)
  {
    arr[init] = 0;
    init++;
  }

  // counting to k,
  // mark the eliminated element
  // print the index of the marked element
  // repeat until only one element is unmarked

  int index;
  int number;
  int num_of_marked;
  number = 1;
  index = 0;
  num_of_marked = 0;
  while (num_of_marked < n - 1)
  {

    if (number == k)
    {
      arr[index] = 1;
      num_of_marked++;
      number = 1;
      printf("%d\n", index);
    }
    else
    {
      index++;
      number++;
      if (index == n)
      {
        index = 0;
      }
    }

    while (arr[index] == 1)
    {
      index++;
      if (index == n)
      {
        index = 0;
      }
    }
  }

  int winner;
  winner = 0;
  while (arr[winner] != 0)
  {
    winner++;
  }
  // print the last one
  printf("%d\n", winner);

  // release the memory of the array
  free (arr);
}
#endif
