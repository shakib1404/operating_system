#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<time.h>
#include<stdlib.h>
#include<unistd.h>


#define Thraednum 2

sem_t semEmpty;
sem_t semFull;

pthread_mutex_t mutex;

int buffer [10];
int count =0;


void* producer(void *args)
{
    while(1){
    int x=rand()%100;
    sleep(1);

 pthread_mutex_lock(&mutex);
 sem_wait(&semEmpty);

    buffer[count]=x;
    count++;

pthread_mutex_unlock(&mutex);
sem_post(&semFull);
    }


}

void* consumer(void *args)
{
    int out ;
    while(1)
    {
   sem_wait(&semFull);
  pthread_mutex_lock(&mutex);

    out=buffer[count-1];
    count--;


    pthread_mutex_unlock(&mutex);
    sem_post(&semEmpty);


    printf("got %d\n",out);
    sleep(1);

    }

}

int main(int argc,char* argv[])
{

    srand((time(NULL)));

    pthread_t th[Thraednum];
    pthread_mutex_init(&mutex,NULL);

    sem_init(&semEmpty,0,10);
    sem_init(&semFull,0,0);

    for(int i=0; i<Thraednum; i++)
    {


        if(i%2==0)
        {
            if(pthread_create(&th[i],NULL,&producer,NULL)!= 0)
            {
                perror("failed to create thread");
            }

            else
            {

                if(pthread_create(&th[i],NULL,&consumer,NULL)!=0)
                    perror("failed to create thread");

            }

        }
    }



    for(int i=0; i<Thraednum; i++)
    {

        if(pthread_join(th[i],NULL)!=0)
        {
            perror("failed to join thread");
        }
    }

  pthread_mutex_destroy(&mutex);
  sem_destroy(&semEmpty);
  sem_destroy(&semFull);

    return 0;
}
