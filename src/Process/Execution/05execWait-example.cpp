/**
 * File             : 05execWait-example.cpp
 * Date of creation : January 1 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * The exec() call family replaces the child process (which is identical to the parents process when forked)
 * by a new one.
 * The following is an example on how to use exec() with your own executable files and wait for the child
 * process to terminate.For this example we will launch the timer (chilProc/time) from this parent process.
 *
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./executable <arg-1>
 * 
 *     - Where <arg-1> is last number to count to. * 
 *     ex : ./executable 3
 *
 * Output :
 * --------------------------------------
 * Parent Process ID : <PID-Parent> .
 * Child Process ID : <PID-Child> .
 * ----------------- .
 * 
 * Timer count: 1 second(s).
 * Timer count: 2 second(s).
 * Timer count: 3 second(s).
 * Timer terminated, parent may now terminate .
 * --------------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/exec
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <sys/wait.h>   // for : wait()

int main(int argc, char *arg[])
{
    if(argc < 2) // Check to make sure the user put argument before executing the script
    {
        printf("Missing argument, try : ./<name-of-file> 3 \n");
        printf("Exiting .\n");
        return 1;
    }

    pid_t childPID;
    childPID = fork(); 

    char *count = arg[1]; // Optionnal, simply makes the code easier to follow

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());
            printf("-----------------\n\n"); // Output formatting

            char *args[3] = {NULL};
            args[0] = "childProc/timer";
            args[1] = count;
            args[2] = NULL;

            int execution = execvp("childProc/timer", args);
            
            if( execution < 0)
            {
                printf("Execution failed with error : %i .\n", errno);
                return 1;
            }
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());
        }
    }
    else if(childPID < 0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    int status;
    wait(&status); // Wait for child process to terminate
    printf("Timer terminated, parent may now terminate .\n");

    return 0;
}