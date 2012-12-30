/**
 * File             : 01fork.cpp
 * Date of creation : December 29 2012
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Creation of a child process and understanding how the chilPID value changes depending on which 
 * process we're in.
 *
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/fork
 * - http://linux.die.net/man/3/errno
 *
 * Output :
 * -----------------------------------
 * Parent Process ID : <PID-Parent> .
 * Child Process ID : <PID-Child> .
 * Child Parent Process ID : <PID-Parent> .
 * Printed by both process : <PID-Parent> .
 * Printed by both process : <PID-Child> .
 * -----------------------------------
 */

#include <unistd.h>     // for : fork()
#include <sys/types.h>  // for : pid_t
#include <stdio.h>      // for : perror, printf
#include <errno.h>      // for : errno

int main(int argc, char *arg[])
{
    pid_t childPID;     // Used to store the processID of the child process after the fork() call
    childPID = fork();  // Creation of a new process (commonly called child process)

    // At this point, when the fork() call returns, a new (identical) process will be created.
    // If we are in the newly created process (the childProcess), the childPID variable will be 0.
    // Otherwise, if we are in the parent process the childPID variable will hold the value of the child PID.
    if(childPID >= 0) // The fork() call was successful
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());
            printf("Child Parent Process ID : %i .\n", getppid());
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());
        }
    }
    else if(childPID <0) // The fork call failed
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    sleep(1); // Simply to make the output clear, printing this text at the end.
    printf("Printed by both process : %i .\n", getpid()); // Code executed by both process

    return 0;
}