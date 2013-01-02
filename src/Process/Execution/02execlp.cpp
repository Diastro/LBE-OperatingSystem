/**
 * File             : 02execlp.cpp
 * Date of creation : January 1 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * The exec() call family replaces the child process (which is identical to the parents process when forked)
 * by a new one.
 * execlp() will lookup the executable file in the PATH environment variable set for your user. If the
 * file isn't found in any of the PATH env folders, the default folder to look into will be the current folder.
 *
 * Output :
 * --------------------------------------
 * Parent Process ID : <PID-Parent> .
 * Child Process ID : <PID-Child> .
 * ----------------- .
 * 
 * total xx
 * -rw-r--r-- 1 <user> <user> 2276 Jan  1 17:36 01execve.cpp
 * -rw-r--r-- 1 <user> <user> 1621 Dec 31 15:50 02execlp.cpp
 * -rw-r--r-- 1 <user> <user> 1621 Jan  1 17:03 03execvp.cpp
 * drwxr-xr-x 2 <user> <user> 4096 Jan  1 16:59 childProc 
 * --------------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/execlp
 *
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>

int main(int argc, char *arg[])
{
    pid_t childPID;
    childPID = fork(); 

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());
            printf("----------------- \n\n"); // Output formatting

            char *args[2] = {NULL};

            args[0] = "ls"; // <from documentation> : By convention, the first of these strings should contain the filename associated with the file being executed.
            args[1] = "-l"; // Argument for ls

            int execution = execlp("ls", args[0], args[1], NULL); // int execlp(const char *file, const char *arg, const char *arg, ... , NULL);

            if( execution < 0) // If the execution is a sucess, the exec() call won't return; If error, it will return -1
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