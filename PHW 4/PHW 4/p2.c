#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#define		size	  16*1024*1024



int main(void){
	int i, j, tmp;
	struct timespec start, stop; 
	double exe_time;
	srand(time(NULL)); 
	int * m = (int *) malloc (sizeof(int)*size);
	for(i=0; i<size; i++){
		m[i]=size-i;
	}
   int teststart = 0;
   int testend = 16;
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	////////**********Your code goes here***************//
	
	quickSort(m,teststart,testend); 	
	printf("\ndone\n");		

	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	  int fail =0;

   for(i=teststart+1; i<testend; i++)
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
	for(i=teststart;i<testend;i++) printf("%d ", m[i]);		
	printf("\nExecution time = %f sec\n",  exe_time);		
}	