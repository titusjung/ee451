#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>


#define thread_num 3
#define consumerGoal 15
#define producerGoal 30
int numCookies =0; 

typedef struct{
	int tid; 
} thread_param;

pthread_mutex_t mutex;
pthread_cond_t emptyCond;
pthread_cond_t fullCond;  
void* thread_consumer_func(void* pthread_arg)
{
	thread_param* myParam = (thread_param*) pthread_arg;  
	int cookiesRetrieved =0;

	while(cookiesRetrieved<consumerGoal)
	{
		pthread_mutex_lock(&mutex); 
		if(numCookies>0)
		{
			numCookies--;
			cookiesRetrieved++;
			printf("Consumer %d has taken %d cookies; # of cookies on shelf changes from %d to %d\n",myParam->tid,cookiesRetrieved,numCookies+1, numCookies); 
		}
        else
        {
            pthread_cond_signal(&fullCond);
            pthread_cond_wait(&emptyCond,&mutex); 
        }
		pthread_mutex_unlock(&mutex);
	}
    //pthread_cond_signal(&fullCond);

}

void* thread_producer_func(void* pthread_arg)
{
	//thread_param myParam = (thread_param*) pthread_arg;  
	int cookiesPlaced =0;
	while(cookiesPlaced<producerGoal)
	{
		pthread_mutex_lock(&mutex); 
		if(numCookies<9)
		{
			numCookies+=2;
			cookiesPlaced+=2;
			printf("Producer has put %d cookies; # of cookies on shelf changes from %d to %d\n",cookiesPlaced,numCookies-2, numCookies); 
            if(numCookies>0)
            {
                pthread_cond_broadcast(&emptyCond);
            }
		}
		else if(numCookies ==9)
		{
			numCookies++;
			cookiesPlaced++;
			printf("Producer has put %d cookies; # of cookies on shelf changes from %d to %d\n",cookiesPlaced,numCookies-1, numCookies); 
		}
        else if(numCookies == 10)
        {
            pthread_cond_wait(&fullCond,&mutex); 
        }
		pthread_mutex_unlock(&mutex);
	}

}

int main(void)
{
   // struct thread_param param1;
   // param1.tid =1; 
  //  struct thread_param param2;
   // param2.tid = 2; 
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_mutex_init(&mutex,NULL);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    pthread_cond_init(&emptyCond,NULL); 
    pthread_cond_init(&fullCond,NULL); 

    thread_param *thread_params = (thread_param* ) malloc(sizeof(thread_param)*thread_num); 
    pthread_t * threads = (pthread_t*)malloc(sizeof(pthread_t)*thread_num); 

    int i,rc;
    for(i=0; i<thread_num; i++)
    {
        thread_param* input = &thread_params[i];
        input->tid = i; 
        if(i==0)
        {
            rc = pthread_create(&threads[i],&attr, thread_producer_func,(void*) &thread_params[i]);
        }
        else
        {
            rc = pthread_create(&threads[i],&attr, thread_consumer_func,(void*) &thread_params[i]);
        }
        if(rc!=0)
        {
            printf("creating thread failed\n"); 
        }
    } 

    pthread_attr_destroy(&attr);
    for(i=0; i<thread_num; i++)
    {
        rc = pthread_join(threads[i],NULL);
        if(rc!=0)
        {
            printf("joining thread failed\n"); 
        }
    }

    pthread_cond_destroy(&emptyCond);
    pthread_cond_destroy(&fullCond);

    pthread_mutex_destroy(&mutex); 
    free(thread_params);
    free(threads); 
    return 0; 
}