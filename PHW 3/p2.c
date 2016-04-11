#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <pthread.h>

#define h  1024 
#define w  1024
#define nClusters 6
#define nRuns 50

#define input_file  "input.raw"
#define output_file "output.raw"

unsigned char *a;

double uArray[nClusters]; 
double sumArray[nClusters];
double noArray[nClusters];

pthread_mutex_t mutex;
pthread_cond_t waitCond;

int r; 

int indexToClosestu(int element);

struct thread_data
{
	int thread_id;
	int startIndex;
	int endIndex; 

	volatile double sumArray[nClusters];
	volatile double noArray[nClusters];
    struct thread_data* threadDataArrayPtr; 
    int numThreads; 


}; 

void* processArray(void *threadarg )
{
	struct thread_data * my_data;
	my_data = (struct thread_data *) threadarg; 
	int i,j;

    for(j=0; j<nRuns; j++)
    {
    	for(i=my_data->startIndex;i<=my_data->endIndex; i++)
    	{
    		int element = a[i];
    		int clusterIndex = indexToClosestu(element);
    		my_data->sumArray[clusterIndex]+=element; 
    		my_data->noArray[clusterIndex]++; 
    	}

        pthread_mutex_lock(&mutex); 
        if(r<my_data->numThreads-1)
        {
            r++;
            pthread_cond_wait(&waitCond,&mutex); 
        }
        else
        {
            r =0; 
            int tt,k;
            for(tt = 0; tt< my_data->numThreads; tt++)
            {
                for(k=0; k<nClusters; k++)
                {
                    //uArray[k] = (double)thread_data_array[tt].sumArray[k]/(double) thread_data_array[tt].noArray[k]; 
                    sumArray[k]+=my_data->threadDataArrayPtr[tt].sumArray[k]; 
                    noArray[k]+=my_data->threadDataArrayPtr[tt].noArray[k]; 
                    my_data->threadDataArrayPtr[tt].sumArray[k]=0; 
                    my_data->threadDataArrayPtr[tt].noArray[k]=0; 
                }
            }

            for(k=0; k<nClusters; k++)
            {
                uArray[k] = sumArray[k]/noArray[k]; 
                sumArray[k]=0; 
                noArray[k]=0 ; 
            }
            pthread_cond_broadcast(&waitCond);

        }
        pthread_mutex_unlock(&mutex);
    }
}

int indexToClosestu(int element)
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

    //int p =4; 

	pthread_attr_t attr;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_cond_init(&waitCond,NULL); 
    pthread_mutex_init(&mutex,NULL);

	if(argc<2)
	{
		printf("not enough arguements\n");
		return 1; 
	}
	int p = atoi(argv[1]);

	//struct thread_data* thread_data_array; 

    //thread_data_array = (struct thread_data*) malloc(sizeof(struct thread_data)*p); 

    struct thread_data thread_data_array[p]; 
	pthread_t threads[p]; 

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



	uArray[0] =0; 
	uArray[1] =65; 
	uArray[2] =100; 
	uArray[3] =125; 
	uArray[4] = 190;
	uArray[5] =255; 

    r =0; 
	for(i=0; i<nClusters; i++)
	{
		sumArray[i]=0; 
		noArray[i]=0 ; 
		for(j=0; j<p; j++)
		{
			thread_data_array[j].sumArray[i]=0; 
			thread_data_array[j].noArray[i]=0; 
            thread_data_array[j].numThreads = p; 
            thread_data_array[j].threadDataArrayPtr = thread_data_array; 
		}
	}
    struct timespec start, stop; 
    double time;        
    if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}

	int tt, rc; 

	for(i=0; i<p; i++)
	{
    	thread_data_array[i].thread_id = i;
    	thread_data_array[i].startIndex = i*w*h/p; 
    	thread_data_array[i].endIndex = (i+1)*w*h/p-1; 	
    	rc = pthread_create(&threads[i],&attr,processArray,(void *) &thread_data_array[i]);
    	if(rc)
    	{
    		printf("ERROR; return code from pthread_create() is%d\n", rc);
    		exit(-1); 
    	}
	}
	pthread_attr_destroy(&attr);

    for(tt = 0; tt< p; tt++)
    {
        rc = pthread_join(threads[tt],NULL); 
        if(rc)
        {
            printf("ERROR; joining thread error return code from pthread_create() is%d\n", rc);
            exit(-1); 
        }            
    }
	//
	for(j=0; j<h*w; j++)
	{

		int element = a[j];
		int clusterIndex = indexToClosestu(element);
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
    pthread_cond_destroy(&waitCond);

    pthread_mutex_destroy(&mutex); 
    return 0;
}