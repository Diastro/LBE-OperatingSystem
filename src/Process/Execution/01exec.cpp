/**
 * File             : 01exec.cpp
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
    pid_t childPID;
    childPID = fork(); 

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            //printf("Child Process ID : %i .\n", getpid());
            char *args[] = {"ls", "-aF", "/", 0}; 
            char *env[] = { 0 };

            printf("About to run /bin/ls\n");
            execve("/bin/ls", args, env);
        }
        else // Code executed in the parent process
        {
            //printf("Parent Process ID : %i .\n", getpid());
        }
    }
    else if(childPID <0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    return 0;
}