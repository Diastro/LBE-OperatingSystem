/**
 * File             : 02semaphore-prodCons.cpp
 * Date of creation : January 4 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to POSIX threads.
 * Dealing with synchronization (mutual exclusion). 
 * Note : Semaphore is like a mutex but it can take a value higher than 1. This example will illustrate how
 * this can be useful using the producer / consumer situation.
 *
 * Processing-buffer : 
 * The main section of our code will fill as many available slots of the processing-buffer (queue) with value and when
 * ever a thread will be available to do work it will go get new value from the processing-buffer (queue). For the
 * sake of this example, the value will be represented as sleeping time (in seconds). 
 *
 * TaskList (time to sleep) :          {3,6,1,7,5,4,8,5,2,1}
 * 
 * 
 * index                    :           0 1 2 3 4           ---> {X}  Thread #1
 * Processing-buffer(queue) :          {X|X|X|X|X}   ---->     
 *                                                          ---> {X}  Thread #2
 * 
 * Execution / Compiling :
 * IMPORTANT : When compiling code using #include <pthread.h>, you need to specify the pthread flag to gcc allowing gcc to link the pthread library
 * 
 *     gcc 01mutex.cpp -o output -pthread
 * 
 * Output : * Order may differ *
 * -----------------------------------
 * Main adding value 1 to processing-buffer .
 * Main adding value 2 to processing-buffer .
 * Main adding value 5 to processing-buffer .
 * Main adding value 8 to processing-buffer .
 * Thread #0 sleeping for 1 from processing-buffer .
 * Main adding value 4 to processing-buffer .
 * Thread #1 sleeping for 2 from processing-buffer .
 * Thread #0 sleeping for 5 from processing-buffer .
 * Main adding value 5 to processing-buffer .
 * Thread #1 sleeping for 8 from processing-buffer .
 * Main adding value 7 to processing-buffer .
 * Thread #0 sleeping for 4 from processing-buffer .
 * Main adding value 1 to processing-buffer .
 * Thread #1 sleeping for 5 from processing-buffer .
 * Main adding value 6 to processing-buffer .
 * Thread #0 sleeping for 7 from processing-buffer .
 * Main informing threads to terminate .
 * Thread #1 sleeping for 1 from processing-buffer .
 * Main informing threads to terminate .
 * Waiting for threads to be done... 
 * Thread #1 sleeping for 6 from processing-buffer .
 * Thread 0 done... 
 * Thread 1 done... 
 * All threads exited... 
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/sem_wait
 * - http://linux.die.net/man/3/sem_post
 * - http://linux.die.net/man/3/sem_init
 * - http://linux.die.net/man/3/sem_destroy
 * - http://en.wikipedia.org/wiki/Semaphore_(programming)
 *
 */

#include <unistd.h>     // for : 
#include <sys/types.h>  // for : pthread_t
#include <stdio.h>      // for : perror, printf
#include <errno.h>      // for : errno
#include <string.h>     // for : strlen
#include <pthread.h>    // for : pthread_create, pthread_join, pthread_exit
#include <semaphore.h>  // for : sem_post, sem_init, sem_wait
#include <cstdlib>      // for : rand()

#define THREAD_COUNT 2
#define TASKLIST_SIZE 10  // Cannot be changed since we manually fill the array in the main of size 10
#define SPOTS 5

// Global variable declaration 
// Allow variable to be accessed from main and thread functions
sem_t queueEmptySpots; // Semaphore indicating the number of empty spots in the queue
sem_t queueFullSpots; // Semaphore indicating the number of non-empty spots in the queue
sem_t IndexMutex; // Mutex used to prevent threads to access / modifiy the reading index at the same time

int writingIndex; // Used by main to add items to the queue
int readingIndex; // Used by threads to remove / read items from the queue

int queue[SPOTS]; 

/**
 * [RandVal]
 * Generated random value between high a low boundaries
 * @param  high Higher bound
 * @param  low  Lower bound
 * @return      Random value
 */
int RandVal(int high, int low)
{
    return (rand() % (high - low + 1)) + low;
}

/**
 * [IncIndex]
 * Increments the value of index by 1
 * @param index [pointer of the value to increment]
 */
void IncIndex(int *index)
{
    if(*index < SPOTS)
    {
        *index = *index + 1; // :)
    }
    else{
        *index = *index % SPOTS;
    }
}

/**
 * [GetIndex]
 * Returns the readingIndex in a thread-safe manner, this way we know that we will never have 2 threads
 * reading the same value
 * @return [readinIndex incremented]
 */
int GetIndex()
{
    sem_wait(&IndexMutex); // Entering critical section

    int index = readingIndex; // Temporary saving to return later
    IncIndex(&readingIndex);

    sem_post(&IndexMutex); // Exiting critical section

    return index;
}

void *ThreadRoutine(void *args)
{
    int threadNum = (int) args;

    while(true)
    {
        sem_wait(&queueFullSpots); // Waits to get the lock and then goes in the processing-buffer to get a sleeping value

        int value = queue[GetIndex()];        
        if(value < 0) break; // If main() sends us a negative value it means that there is nothing else to process, thread may terminate
        printf("Thread #%i sleeping for %i from processing-buffer .\n", threadNum, value);
        sleep(value); // Does work aka sleeps

        sem_post(&queueEmptySpots); // main() may now add a new value since we processed one
    }

    pthread_exit(NULL);
}

int main(int argc, char *arg[])
{
    int taskList[TASKLIST_SIZE] = {3,6,1,7,5,4,8,5,2,1};

    readingIndex = 0; // Queue index init.
    writingIndex = 0; // Queue index init.

    sem_init(&queueEmptySpots, 0, SPOTS); // Init with the number of available spots in our array and we will decrement the semaphoe until there's no more spots avaialble
    sem_init(&queueFullSpots, 0, 0); // This semaphore will do the oposite of the queueEmptySpots and will be incremented when ever we add value to our array
    sem_init(&IndexMutex, 0, 1); // Simply to prevent a double access from 2 thread to the readingIndex value

    pthread_t threadId[THREAD_COUNT];

    for(int i=0; i<THREAD_COUNT; i++)
    {
        int pthreadReturn = pthread_create(&threadId[i], NULL, ThreadRoutine, (void *) i); 
        if (pthreadReturn != 0)
        {
            printf("Error creation failed with error: %i .\n", pthreadReturn);
            break;
        }
    }

    //Adding items to the queue (stops if there no more room aka thread are all busy)
    int processedItems = TASKLIST_SIZE-1;
    while(processedItems > 0)
    {
        sem_wait(&queueEmptySpots); // Entering critical section 

        printf("Main adding value %i to processing-buffer .\n", taskList[processedItems]);
        queue[writingIndex] = taskList[processedItems];
        IncIndex(&writingIndex);
        processedItems--;

        sem_post(&queueFullSpots); // Exiting critical section
    }

    // We send a negative number to all threads to inform them that everything was processed
    int threadToKill = THREAD_COUNT;
    while(threadToKill > 0)
    {
        sem_wait(&queueEmptySpots); // Entering critical section

        printf("Main informing threads to terminate .\n");
        queue[writingIndex] = -1; // Sending value to the thread by adding it to the processing-queue
        IncIndex(&writingIndex); // Increment the writing index
        threadToKill--;

        sem_post(&queueFullSpots); // Exiting critical section
    }

    printf("Waiting for threads to be done... \n");

    // Waiting for threads to exit
    for(int j=0; j<THREAD_COUNT; j++)
    {
        pthread_join(threadId[j], NULL);
        printf("Thread %i done... \n", j);
    }

    sem_destroy(&queueEmptySpots); // Clean up, desalocate the memory pointed by mutex
    sem_destroy(&queueFullSpots); // Clean up, desalocate the memory pointed by mutex
    printf("All threads exited... \n");

    return 0;
}
