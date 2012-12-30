/**
 * File             : 02waitpid-elaborated.cpp
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
            sleep(2);
            
            return 2; // Makes the child process terminates with a specific value
        }
        else
        {
            printf("Parent Process ID : %i .\n", getpid());

            int status;
            int waitValue = waitpid(childPID, &status, WCONTINUED);

            if(waitValue == childPID) // Child process terminated
            {
                printf("Child process terminated .\n");

                if (WIFEXITED(status)) // Child process was terminated normally
                {
                    printf("Child process terminated with value %i .\n", WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status)) // Child process was terminated on a signal
                {
                    printf("Child process terminated due to signal %i .\n", WTERMSIG(status));
                }
                else if (WIFSTOPPED(status)) // Child process was stopped
                {
                    printf("Child process was stopped by signal %i .\n", WIFSTOPPED(status));
                }
            }
            else
            {
                printf("Waitpid error : %i .\n", errno);
            }

        }
    }
    else if(childPID <0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    return 0;
}