/**
 * File             : 04exec-example.cpp
 * Date of creation : January 1 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * The exec() call family replaces the child process (which is identical to the parents process when forked)
 * by a new one.
 * The following is an example on how to use exec() with your own executable files
 *
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./executable <arg-1> <arg-2>
 * 
 *     - Where <arg-1> is the name of the object you want to counting.
 *     - Where <arg-2> is last number to count to. * 
 *     ex : ./executable cars 3
 *
 * Output :
 * --------------------------------------
 * Parent Process ID : <PID-Parent> .
 * Child Process ID : <PID-Child> .
 * ----------------- .
 * 
 * Counting : 1 car .
 * Counting : 2 car .
 * Counting : 3 car .
 * Counting : 4 car .
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

int main(int argc, char *arg[])
{
    if(argc < 3) // Check to make sure the user put argument before executing the script
    {
        printf("Missing argument, try : ./<name-of-file> car 3 \n");
        printf("Exiting .\n");
        return 1;
    }

    pid_t childPID;
    childPID = fork(); 

    char *objectName = arg[1];// Optionnal, simply makes the code easier to follow
    char *count = arg[2]; // Optionnal, simply makes the code easier to follow

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());
            printf("----------------- \n\n"); // Output formatting

            char *args[4] = {NULL};

            args[0] = "childProc/counter";
            args[1] = objectName;
            args[2] = count;
            args[3] = NULL;

            int execution = execvp("childProc/counter", args);
            
            if( execution < 0)
            {
                printf("Execution failed with error : %i .\n", errno);
            }
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());
        }
    }
    else if(childPID <0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    return 0;
}