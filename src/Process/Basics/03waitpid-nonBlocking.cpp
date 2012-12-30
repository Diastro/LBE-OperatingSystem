/**
 * File             : 03waitpid-nonBlocking.cpp
 * Date of creation : December 29 2012
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Waiting for a SPECIFIC child process to finish (exit) in a non-blocking manner before continuing the execution of the parent process.
 * This allows the parent process to keep working on other tasks while waiting for the child process to terminate.
 *
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/wait
 */

#include <unistd.h> 
#include <sys/types.h> 
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>   // for : wait()

int main(int argc, char *arg[])
{
    pid_t childPID;     
    childPID = fork();  
    
    if(childPID >= 0)
    {
        if(childPID == 0)
        {
            printf("Child Process ID : %i .\n", getpid());
            sleep(3); // Makes the child process do some work for it's parent to wait until it finishes
        }
        else // Code executed by parent process
        {
            printf("Parent Process ID : %i .\n", getpid());

            int status, waitValue;
        
            while (1) 
            {   
                waitValue = waitpid(childPID, &status, WNOHANG); // See references for available option flag; WNOHANG make the wait call non-blocking allowing the parent process to do some work while waiting for child process

                if (waitValue == childPID){
                    printf("Child process terminated : %i .\n", waitValue);
                    break;
                }
                else if (waitValue ==  -1) // Error while retrieving the status of the child process
                {
                    printf("Waitpid error : %i .\n", errno);
                    break;
                }
                else if (waitValue ==  0) // Child not terminated yet
                {
                    printf("Parent process is doing work while waiting .\n");
                    sleep(1); // Simulated workwork for the parent process
                }

            }

            printf("Child process terminated, parent process may now terminate .\n");

        }
    }
    else if(childPID <0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    return 0;
}