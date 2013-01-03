/**
 * File             : 02thread-multipleTasks.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to POSIX threads.
 * Handling multiple threads / tasks.
 *
 * Execution / Compiling :
 * IMPORTANT : When compiling code using #include <pthread.h>, you need to specify the pthread flag to gcc allowing gcc to link the pthread library
 * 
 *     gcc 02thread-multipleTasks.cpp -o output -pthread
 * 
 * Output :
 * -----------------------------------
 * Creating threads... 
 * Doing work (thread #0)... 
 * Doing work (thread #2)... 
 * Doing work (thread #1)... 
 * All threads exited...
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/pthread_create
 * - http://linux.die.net/man/3/pthread_exit
 * - http://linux.die.net/man/3/pthread_join
 *
 */

#include <unistd.h>     // for : 
#include <sys/types.h>  // for : pthread_t
#include <stdio.h>      // for : perror, printf
#include <errno.h>      // for : errno
#include <string.h>     // for : strlen
#include <pthread.h>    // for : pthread_create, pthread_join, pthread_exit

#define THREAD_COUNT 3

void *DoWork(void *args)
{
    int threadNum = (int) args; // Casting arguments
    printf("Doing work (thread #%i)... \n", threadNum);
    sleep(1); // Working

    pthread_exit(NULL);
}

int main(int argc, char *arg[])
{
    printf("Creating threads... \n");

    pthread_t threadId[THREAD_COUNT]; // Structure holding the thread ID

    for(int i=0; i<THREAD_COUNT; i++)
    {
        int pthreadReturn = pthread_create(&threadId[i], NULL, DoWork, (void *) i); // Thread creation

        if (pthreadReturn != 0) // If return value isn't 0  pthread_create will return the error number
        {
            printf("Error creation failed with error: %i .\n", pthreadReturn);
            break;
        }
    }

    for(int j=0; j<THREAD_COUNT; j++)
    {
        pthread_join(threadId[j], NULL); // Waits for the thread to finish it's work
    }

    printf("All threads exited...\n");

    return 0;
}