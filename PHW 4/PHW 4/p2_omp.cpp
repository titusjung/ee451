#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>
#define		size	   16*1024*1024

void quickSort(int *array, int start, int end){
   // you quick sort function goes here  
   int length = end -start; 
   if(length<=1) return;
   int * lowPivot = (int *) malloc (sizeof(int)*length);
   int * highPivot = (int *) malloc (sizeof(int)*length);

  // int lowPivot[length];
   int l=0; 
   int h=0; 
   //int highPivot[length];
   int pivotIndex = (int)rand()%length+start;/*
   std::cout<<"pivot index is "<<pivotIndex<<std::endl; 
   printf("pivot index is %d\n", pivotIndex);*/
   int pivot = array[pivotIndex];
   int i;
   
   //std::cout<<"pivot is "<<pivot<<std::endl;

   for(i=start; i<end; i++)
   {
   		if(i==pivotIndex) continue;
   		else if(array[i]>pivot)
   		{
   			highPivot[h]=array[i];
   			h++;
   			//std::cout<<"high number  is "<<array[i]<<std::endl; 

   		}
   		else
   		{
   			//std::cout<<"low number  is "<<array[i]<<std::endl; 

   			lowPivot[l]=array[i];
   			l++;
   		}
   }
   /*
   std::cout<<"pivot change is "<<std::endl; 
   for(i=0; i<l; i++)
   {
   	std::cout<<" "<<lowPivot[i];
   }

   std::cout<<std::endl<<pivot<<std::endl;; 

   for(i=0; i<h; i++)
   {
   	std::cout<<" "<<highPivot[i];
   }
   std::cout<<std::endl; */
   #pragma omp parallel num_threads(2)
   {
   		#pragma omp sections
   		{
   			#pragma omp section
   			quickSort(lowPivot,0,l);
   			#pragma omp section
   			quickSort(highPivot,0,h);
   		}
   }


   for(i=0; i<l; i++)
   {
   		array[i+start] = lowPivot[i];
   }
   array[l+start] = pivot;

   for(i=0; i<h; i++)
   {
   		array[l+1+i+start] = highPivot[i];
   }
   free(lowPivot);
   free(highPivot);
/*
   std::cout<<"sorted array is"<<std::endl;
   for(i=0; i<length;i++)
   {
   		std::cout<<" "<<array[i];
   }
   std::cout<<std::endl;
*/
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
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
	////////**********Your code goes here***************//
	
	quickSort(m,20,100); 	
	printf("\ndone\n");		

	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	
	for(i=20;i<100;i++) printf("%d ", m[i]);		
	printf("\nExecution time = %f sec\n",  exe_time);		
}	