/* MODIFY this file */

#include "sort.h"

void ssort(int * arr, int size) {

	/* For step 3, fill this in to perform a selection sort
	   For step 4, add conditional compilation flags to perform an ascending selection sort instead */
	
	int i;
	int j;
	int temp;
	int m;	
	int m_index;

	for (i = 0; i < size - 1; i++)
	{
		m = arr[i];
		m_index = i;
		for (j = i + 1; j < size; j++)
		{
#ifdef ASCENDING
			if (arr[j] < m)
#else 
			if (arr[j] > m)
#endif
			{
				m = arr[j];
				m_index = j;
			}
		}

		temp = arr[i];
		arr[i] = arr[m_index];
		arr[m_index] = temp;	
	}
}
