#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <pthreads.h>
#define NUM_THREADS 5

struct thread_data
{
	int thread_id;
	int startIndex;
	int endIndex; 

	double **A;
	double **B;
	double **C; 
	int n; 
};
struct thread_data thread_data_array[NUM_THREADS]; 
void *Multiply(void *threadarg)
{
	struct thread_data * my_data;
	my_data = (struct thread_data *) threadarg; 
	double ** a = my_data->A; 
	double ** b =my_data->B; 
	double ** c =my_data->C;  

	int i,j,k; 
	for(i = my_data->startIndex; i<=my_data->endIndex; i++)
	{
		for(j =0; j<my_data->n; j++)
		{
			for(k= 0; k<my_data->n; k++)
			{
				c[i][j]+=a[i][k]*b[k][j]
			}
		}
	}

}

int main(void){
		int i, j, k;

		pthread_t threads[NUM_THREADS]; 
		pthread_attr_t attr;

		struct timespec start, stop; 
		double time;
		int n = 4096; // matrix size is n*n
		
		double **A = (double**) malloc (sizeof(double*)*n);
		double **B = (double**) malloc (sizeof(double*)*n);
		double **C = (double**) malloc (sizeof(double*)*n);

		pthread_attr_init(&attr);
		pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

		for (i=0; i<n; i++) {
			A[i] = (double*) malloc(sizeof(double)*n);
			B[i] = (double*) malloc(sizeof(double)*n);
			C[i] = (double*) malloc(sizeof(double)*n);
		}
		
		for (i=0; i<n; i++){
			for(j=0; j< n; j++){
				A[i][j]=i;
				B[i][j]=i+j;
				C[i][j]=0;			
			}
		}
				
		if( clock_gettime(CLOCK_REALTIME, &start) == -1) { perror("clock gettime");}
		
		// Your code goes here //
		// Matrix C = Matrix A * Matrix B //	
		//*******************************//
		int tt, rc;
		for(tt = 0; tt< NUM_THREADS; tt++)
		{
			thread_data_array[tt].thread_id = tt;
			thread_data_array[tt].startIndex = tt*n/p; 
			thread_data_array[tt].endIndex = (tt+1)*n/p-1; 			

			thread_data_array[tt].A = A;
			thread_data_array[tt].B = B;
			thread_data_array[tt].C = C;
			thread_data_array[tt].n = n; 

			rc = pthread_create(&threads[i],NULL,Multiply,(void *) thread_data_array[tt]);
			if(rc)
			{
				printf("ERROR; return code from pthread_create() is%d\n", rc);
				exit(-1); 
			}
		}
		pthread_attr_destroy(&attr);
		for(tt = 0; tt< NUM_THREADS; tt++)
		{
			rc = pthread_join(thread[t],NULL); 
			if(rc)
			{
				printf("ERROR; joining thread error return code from pthread_create() is%d\n", rc);
				exit(-1); 
			}			 
		}		

		for(i=0; i<n; i++)
		{
			for(j=0; j<n; j++)
			{
				for(k=0; k<n; k++)
				{
					C[i][j]+=A[i][k]*B[k][j]; 
				}
			}
		}
		
		//*******************************//
		
		if( clock_gettime( CLOCK_REALTIME, &stop) == -1 ) { perror("clock gettime");}		
		time = (stop.tv_sec - start.tv_sec)+ (double)(stop.tv_nsec - start.tv_nsec)/1e9;
		
		printf("Number of FLOPs = %lu, Execution time = %f sec,\n%lf MFLOPs per sec\n", (long unsigned int)2*n*n*n, time, 1/time/1e6*2*n*n*n);		
		printf("C[100][100]=%f\n", C[100][100]);
		
		// release memory
		for (i=0; i<n; i++) {
			free(A[i]);
			free(B[i]);
			free(C[i]);
		}
		free(A);
		free(B);
		free(C);
		return 0;
}
