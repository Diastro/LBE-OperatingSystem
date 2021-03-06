/**
 * File             : 04wait.cpp
 * Date of creation : December 30 2012
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Waiting for ALL child process to finish (exit) before continuing the execution of the parent process.
 *
 * Output :
 * -----------------------------------
 * Child #0 created .
 * Child #1 created .
 * Child #0 work's is done .
 * Child #1 work's is done .
 * Job complete, exiting .
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/wait
 *
 */

#include <unistd.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>   // for : wait()

int main(int argc, char *arg[])
{
    int const CHILD_COUNT = 2; // Set a fix number of child process to create
    pid_t childPID;
    
    for(int i=0; i<2; i++){ // Loops twice to create 2 child process
        childPID = fork();

        if(childPID >= 0)
        {
            if(childPID == 0)
            {
                printf("Child #%i created .\n", i);
                sleep(2); // Makes the child process do some work for it's parent to wait until it finishes
                printf("Child #%i work's is done .\n", i);

                return 2; // Terminate the child process
            }
        }
        else if(childPID <0)
        {
            printf("Fork failed with error code : %i .\n", errno);
            return 1;
        }
    }

    for(int j=0; j<CHILD_COUNT; j++) // Wait for as many child process there is to terminate
    {
        int status;
        wait(&status); // Wait for any child process to terminate
    }

    printf("Job complete, exiting .\n");

    return 0;
}
