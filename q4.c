#define _XOPEN_SOURCE 700
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#define NUMBERS 10

int buf[5];
int index = -1;
sem_t semaphore;

void* producer(void* args)
{
    int* array = (int *)args;
    for (int i=0; i< 10; i++)
    {   
        int r = rand() % 3;
        sleep (r);
        //wait
        sem_wait(&semaphore);    
        
        
        //critical section
        index++;
        buf[index] = array[i];
        
        //signal
        
        printf("Produced: %d\n", array[i]);
        sem_post(&semaphore);
    }
    pthread_exit(NULL);
}

void* consumer(void* args)
{
    int flag = 1;
    int count = 0;
    while (flag)
    {

        int r = rand() % 3;
        sleep (r);

        //wait
        sem_wait(&semaphore);
        
        //critical section 
        if (index < 0 )
        {
            count++;
            sem_post(&semaphore);
        }

        else 
        {
            
            int val = buf[index];
            buf[index] = 0;
            index--;
            
            //signal
            printf("Consumed: %d\n", val);
            sem_post(&semaphore);
            count++;
            
        }
        if (count > 20){
            flag = 0;
        }
        
    }
    pthread_exit(NULL);
}

int main()
{
    int arr[NUMBERS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
   /*
    printf("Plese enter a number.\n");
    scanf("%d", &arr[0] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[1] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[2] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[3] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[4] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[5] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[6] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[7] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[8] );
    printf("Plese enter a number.\n");
    scanf("%d", &arr[9] );
    */
    
    sem_init(&semaphore, 0, 1);
    pthread_t pro, con;
    if(pthread_create(&pro, NULL, &producer, (void*)&arr))
    {
        printf("Could not create thread\n");
        return -1;
    }
    if(pthread_create(&con, NULL, &consumer, (void*)&arr))
    {
        printf("Could not create thread\n");
        return -1;
    }
    pthread_join(pro, NULL);
    pthread_join(con, NULL);
    printf("Buffer: [%d, %d, %d, %d, %d]\n", buf[0], buf[1], buf[2], buf[3], buf[4]);
    return 0;
}