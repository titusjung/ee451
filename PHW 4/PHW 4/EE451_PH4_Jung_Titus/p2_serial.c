#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define		size	  16*1024*1024


void swap(int *arr, int aIndex, int bIndex)
{
	int temp = arr[aIndex];
	arr[aIndex] = arr[bIndex];
	arr[bIndex] = temp;

}

int partition(int* arr, int start, int end, int pivotIndex)
{
	if (!(pivotIndex>start && pivotIndex<end)) return -1;
	int pivot = arr[pivotIndex];
	int i, j, k;
	i = start;
	j = end-1;
	while (i<j)
	{
		while (arr[i] <= pivot && i < end) { i++; }
		while (arr[j]>pivot && j>=start) { j--; }
		if (i >= j) break;
		swap(arr, i, j);
	}

	return j;
}

void quickSort(int *arr, int start, int end)
{
	if (start<end)
	{
		int pivotIndex = (end - start) / 2 + start; 
		int p = partition(arr, start, end,  pivotIndex);
		if (p == -1) return;
		quickSort(arr, start, p);
		quickSort(arr, p + 1, end);
	}
}


int main(void) {
	int i, j, tmp;
	struct timespec start, stop;
	double exe_time;
	srand(time(NULL));
	int * m = (int *)malloc(sizeof(int)*size);
	for (i = 0; i<size; i++) {
		m[i] = size - i;
	}
	int teststart = 0;
	int testend = size;
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}

	////////**********Your code goes here***************//

	quickSort(m, teststart, testend);

	///////******************************////
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	int fail = 0;

	for (i = teststart + 1; i<testend; i++)
	{
		if (m[i - 1]>m[i])
		{
			fail = 1;
			break;
		}
	}
	if (!fail)
	{
		printf("\n Quicksort success!\n");

	}
	else
	{
		printf("\n Quicksort FAIL\n");
		//free(m);
		// return;
	}
	//printArr(m, teststart, testend);
	for (i = 0;i<16;i++) printf("%d ", m[i]);
	free(m);
	printf("\nExecution time = %f sec\n",  exe_time);		

	return 1;

}