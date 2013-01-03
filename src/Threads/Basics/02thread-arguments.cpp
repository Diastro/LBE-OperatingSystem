/**
 * File             : 02thread-arguments.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to POSIX threads. Passing arguments to threads.
 *
 * Execution / Compiling :
 * IMPORTANT : When compiling code using #include <pthread.h>, you need to specify the pthread flag to gcc allowing gcc to link the pthread library
 * 
 *     gcc 02thread-arguments.cpp -o output -pthread
 * 
 * Output :
 * -----------------------------------
 * Creating thread with ID : <Thread-ID> .
 * Inside ThreadA() function of threadID : <Thread-ID> .
 * Thread exited...
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

void *ThreadA(void *args)
{
    printf("Inside ThreadA() function of threadID : %i .\n", args);
    pthread_exit(NULL);
}

int main(int argc, char *arg[])
{
    pthread_t threadId; // Set initial ID for the thread

    printf("Creating thread with ID : %i .\n", threadId);
    int pthreadReturn = pthread_create(&threadId, NULL, ThreadA, (void *) threadId); // Passes the threadId pointer as argument for the Thread

    if (pthreadReturn != 0) 
    {
        printf("Error creation failed with error: %i .\n", pthreadReturn);
        return 1;
    }

    pthread_join(threadId, NULL); // Waits for the thread to finish it's work

    printf("Thread exited...\n");

    return 0;
}