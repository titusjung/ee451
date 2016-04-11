#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define h  800 
#define w  800
#define nClusters 6
#define nRuns 50

#define input_file  "input.raw"
#define output_file "output.raw"




unsigned char *a; 
int indexToClosestu(int element, double uArray[nClusters]);

struct thread_data
{
	int thread_id;
	int startIndex;
	int endIndex; 

	double sumArray[nClusters];
	double noArray[nClusters];
	double uArray[nClusters];
}; 

void* processArray(void *threadarg )
{
	struct thread_data * my_data;
	my_data = (struct thread_data *) threadarg; 
	int i;
	for(i=0; i<nClusters; i++)
	{
		sumArray[i]=0;
		noArray[i]=0; 
	}	
	for(i=startIndex;i<endIndex; i++)
	{
		int element = a[i];
		int clusterIndex = 
	}
}

int indexToClosestu(int element, double uArray[nClusters])
{
	double diff =fabs(element-uArray[0]); 
	int index =0;
	int i=1;
	for(i=1; i<nClusters; i++)
	{
		double tempDiff = fabs(element -uArray[i]); 
		if(tempDiff<diff)
		{
			index =i;
			diff = tempDiff;
		}
	}

	return index; 

}



int main(int argc, char** argv){
   int i,j,k;
    FILE *fp;

	int i, j, k;
	if(argc<2)
	{
		printf("not enough arguemnets\n");
		return 1; 
	}
	int p = atoi(argv[1]);

  	a = (unsigned char*) malloc (sizeof(unsigned char)*h*w);
    
	// the matrix is stored in a linear array in row major fashion
	if (!(fp=fopen(input_file, "rb"))) {
		printf("can not opern file\n");
		return 1;
	}
	fread(a, sizeof(unsigned char), w*h, fp);
	fclose(fp);
    
	// measure the start time here
	//  Your code goes here
	struct timespec start, stop; 
	double time;		
	if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}

	double uArray[nClusters]; 

	uArray[0] =0; 
	uArray[1] =65; 
	uArray[2] =100; 
	uArray[3] =125; 
	uArray[4] = 190;
	uArray[5] =255; 

	double sumArray[nClusters];
	double noArray[nClusters];

	for(i=0; i<nClusters; i++)
	{
		sumArray[i]=0; 
		noArray[i]=0 ; 
	}




	for(i=0; i<nRuns; i++)
	{
		for(j=0; j<h*w; j++)
		{

				int element = a[j];
				int clusterIndex = indexToClosestu(element, uArray);
				sumArray[clusterIndex]+=element; 
				noArray[clusterIndex]++; 
			
		}

		for(j=0; j<nClusters; j++)
		{
			uArray[j] = sumArray[j]/noArray[j]; 
			sumArray[j]=0; 
			noArray[j]=0 ; 
		}
	}
		
	//
	for(j=0; j<h*w; j++)
	{

			int element = a[j];
			int clusterIndex = indexToClosestu(element, uArray);
			a[j]=uArray[clusterIndex]; 
		
	}	
	// measure the end time here
	
	// print out the execution time here
	if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
	time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
	
	printf(" Execution time = %f sec", time);			
	
	if (!(fp=fopen(output_file,"wb"))) {
		printf("can not opern file\n");
		return 1;
	}	
	fwrite(a, sizeof(unsigned char),w*h, fp);
    fclose(fp);
    
    return 0;
}