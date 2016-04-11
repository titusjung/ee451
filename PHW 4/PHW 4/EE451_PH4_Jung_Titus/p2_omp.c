#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#define		size	16*1024*1024
 //wikipedia based code
void swap(int *arr, int aIndex, int bIndex)
{
	int temp = arr[aIndex];
	arr[aIndex] = arr[bIndex];
	arr[bIndex] = temp;

}

int partition(int* arr, int start, int end, int pivotIndex)
{
	if (!(pivotIndex>=start && pivotIndex<end)) return -1;
	int pivot = arr[pivotIndex];
	int i, j, k;
	i = start;
	j = end-1;
	while (i<j)
	{
		while (arr[i] <= pivot && i < j) { i++; }
		while (arr[j]>pivot && j>=i) { j--; }
		if (i >= j) break;
		swap(arr, i, j);
	}

	return j;

}

void quickSort(int *arr, int start, int end)
{
	if(start-end==2)
	{
		if(arr[start]>arr[end]) swap(arr,start,end);
	}
	else if (start<end)
	{
		int pivotIndex = (end - start) / 2 + start; 
		int p = partition(arr, start, end,  pivotIndex);
		if (p == -1) return;
		quickSort(arr, start, p);
		quickSort(arr, p + 1, end);
	}
}

int main(void){
	int i, j, tmp;
	struct timespec start, stop; 
	double exe_time;
	srand(time(NULL)); 
	int * m = (int *) malloc (sizeof(int)*size);
	for(i=0; i<size; i++){
		m[i]=size-i;
	}


	int pivotIndex = (int)rand()%size;

	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	////////**********Your code goes here***************//

	int p = partition(m,0,size,pivotIndex);
   #pragma omp parallel num_threads(2)
   {
   		#pragma omp sections
   		{
   			#pragma omp section
   			quickSort(m,0,p+1);
   			#pragma omp section
   			quickSort(m,p-1,size);
   		}
   }




	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	printf("\ndone\n");		

	int fail =0;
	for(i=1; i<size; i++)
	{
		if(m[i-1]>m[i])
		{
			fail =1;
			break;
		}
	}
	if(!fail)
	{
		printf("\n Quicksort success!\n");		

	}
	else
	{
		printf("\n Quicksort FAIL\n");		
      //free(m);
     // return;
	}

	for(i=0;i<16;i++) printf("%d ", m[i]);

	printf("\nExecution time = %f sec\n",  exe_time);		
      free(m);

}	