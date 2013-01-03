/**
 * File             : 01thread.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to POSIX threads.
 *
 * Execution / Compiling :
 * IMPORTANT : When compiling code using #include <pthread.h>, you need to specify the pthread flag to gcc allowing gcc to link the pthread library
 * 
 *     gcc 01thread.cpp -o output -pthread
 * 
 * Output :
 * -----------------------------------
 * Creating thread with ID : <Thread-ID> .
 * Inside ThreadA() function .
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
#include <pthread.h>    // for pthread_create, pthread_join, pthread_exit

void *ThreadA(void *args)
{
    printf("Inside ThreadA() function .\n");
    pthread_exit(NULL);
}

int main(int argc, char *arg[])
{
    pthread_t tId; // Structure holding the thread ID

    printf("Creating thread with ID : %i .\n", tId);
    int pthreadReturn = pthread_create(&tId, NULL, ThreadA, NULL); // Thread creation

    if (pthreadReturn != 0) // If return value isn't 0  pthread_create will return the error number
    {
        printf("Error creation failed with error: %i .\n", pthreadReturn);
        return 1;
    }

    pthread_join(tId, NULL); // Waits for the thread to finish it's work

    printf("Thread exited...\n");

    return 0;
}