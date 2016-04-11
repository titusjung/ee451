#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <omp.h>
#include <iostream>
#define		size	   16*1024*1024


void swap(int *array, int aIndex, int bIndex)
{
   int temp = array[aIndex];
   array[aIndex] = array[bIndex];
   array[bIndex] = temp;

}

//using code from book; 
void quickSort(int *array, int start, int end)
{
   if(start>=end) return;

   int i,x,s;
   x = array[start];
   s= start; 
   for(i=start+1; i<end;i++)
   {
      if(array[i]<=x)
      {
         s++;
         swap(array,s,i);

      }
   }
   swap(array,start,s);

   for(i=start;i<s;i++)
   {
      std::cout<<" "<<array[i];
   }
   std::cout<<std::endl<<" "<<array[s];
   for(i=s+1;i<end;i++)
   {
      std::cout<<" "<<array[i];
   }
   std::cout<<std::endl;


   quickSort(array,start,s);
   quickSort(array,s,end);

}
/*
void quickSort(int *array, int start, int end){
   int length = end -start; 
   if(length<=1) return;
   int * lowPivot = (int *) malloc (sizeof(int)*length);
   int * highPivot = (int *) malloc (sizeof(int)*length);

   int l=0; 
   int h=0; 
   int pivotIndex = (int)rand()%length+start;
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

	quickSort(lowPivot,0,l);
	quickSort(highPivot,0,h);

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

}
*/
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
	
	quickSort(m,0,16); 	
	printf("\ndone\n");		

	///////******************************////
	
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	exe_time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
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
      free(m);
      return 1;
   }
	for(i=0;i<20;i++) printf("%d ", m[i]);		
	printf("\nExecution time = %f sec\n",  exe_time);		
   return 0; 
}	