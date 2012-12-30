/**
 * File             : 02waitpid-basic.cpp
 * Date of creation : December 29 2012
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Waiting for a SPECIFIC child process to finish (exit) before continuing the execution of the parent process.
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
            sleep(2); // Makes the child process do some work for it's parent to wait until it finishes
        }
        else // Code executed by parent process
        {
            printf("Parent Process ID : %i .\n", getpid());

            int status;
            int waitValue = waitpid(childPID, &status, WCONTINUED); // This call will block until the child process reaches a terminated state (or until the child process returns with errors)
           
            if(waitValue == childPID) // child process terminated
            {
                printf("Child process terminated .\n");
            }
            else // something wrong happened while obtaining the status
            {
                printf("Waitpid error : %i .\n", errno);
            }

        }
    }
    else if(childPID <0)
    {
        printf("\n Fork failed with error code : %i .\n", errno);
        return 1;
    }

    return 0;
}