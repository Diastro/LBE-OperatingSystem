/**
 * File             : 01mutex.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to POSIX threads.
 * Dealing with synchronization (mutual exclusion). 
 * Note : A mutex is a binary semaphore. It only takes the value 0 or 1.
 *
 * Execution / Compiling :
 * IMPORTANT : When compiling code using #include <pthread.h>, you need to specify the pthread flag to gcc allowing gcc to link the pthread library
 * 
 *     gcc 01mutex.cpp -o output -pthread
 * 
 * Output :
 * -----------------------------------
 * In main, value = 0 .
 * Thread #0 : value = 2 .
 * Thread #1 : value = 4 .
 * Thread #2 : value = 6 .
 * Thread #3 : value = 8 .
 * All threads exited...
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/sem_wait
 * - http://linux.die.net/man/3/sem_post
 * - http://linux.die.net/man/3/sem_init
 * - http://linux.die.net/man/3/sem_destroy
 *
 */

#include <unistd.h>     // for : 
#include <sys/types.h>  // for : pthread_t
#include <stdio.h>      // for : perror, printf
#include <errno.h>      // for : errno
#include <string.h>     // for : strlen
#include <pthread.h>    // for : pthread_create, pthread_join, pthread_exit
#include <semaphore.h>  // for : sem_post, sem_init, sem_wait

#define THREAD_COUNT 4

// Global variable declaration 
// Allow variable to be accessed from main and thread functions
int value;
sem_t mutex;

void *IncrementFunc(void *args)
{
    int threadNum = (int) args;

    // Critical section
    // Increments the variable value by +2 and then sleep for 1 second
    sem_wait(&mutex); // At this point all the thread are trying to decrement thre mutex to 0. If the mutex already has a value of 0, the calling thread blocks here 
    value += 2;
    printf("Thread #%i : value = %i .\n", threadNum, value);
    sleep(1);
    sem_post(&mutex); // Increment the value of the mutex by one (allowing an other thread the decrement it's value and getting the lock)
    // End of critical section

    pthread_exit(NULL);
}

int main(int argc, char *arg[])
{
    pthread_t threadId[THREAD_COUNT];
    value = 0; // Assigning a value to the shared variable
    printf("In main, value = %i .\n", value);

    sem_init(&mutex, 0, 1); // Initial value of the mutex is 1 (allowing a thread to get a lock on a critical region)

    for(int i=0; i<THREAD_COUNT; i++)
    {
        int pthreadReturn = pthread_create(&threadId[i], NULL, IncrementFunc, (void *) i); 

        if (pthreadReturn != 0)
        {
            printf("Error creation failed with error: %i .\n", pthreadReturn);
            break;
        }
    }

    for(int j=0; j<THREAD_COUNT; j++)
    {
        pthread_join(threadId[j], NULL);
    }

    sem_destroy(&mutex); // Clean up, desalocate the memory pointed by mutex
    printf("All threads exited...\n");

    return 0;
}