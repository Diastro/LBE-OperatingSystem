/**
 * File             : 02pipe-interProc-elaborated.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to unnamed pipe between 2 process which aren't sharing the same codebase. We will pass the file descriptor from
 * the parent to the child process as argument and then establish communication.
 *
 * ParentProc (writing):
 *                          open                                 close                                             
 *              write() --> fd[1] -- |======= PIPE#1 =======| -- fd[0] --> read() 
 *
 * ChildProc (reading):
 *                          close                                open                                             
 *              write() --> fd[1] -- |======= PIPE#1 =======| -- fd[0] --> read() 
 *
 * Output :
 * -----------------------------------
 * Parent Process ID : <PID-Parent> .
 * Parent is sending message to child process using file descriptor <FD#> .
 * Child Process ID : <PID-Child> .
 * Child process is reading from file descriptor <FD#> .
 * Child process received message : "This is a message!" .
 * Child process terminated, parent may now terminate .
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/2/read
 * - http://linux.die.net/man/2/write
 * - http://linux.die.net/man/2/close
 * - http://linux.die.net/man/2/pipe
 *
 */

#include <unistd.h>     // for : read, write, close, pipe
#include <sys/types.h>  // for : 
#include <stdio.h>      // for : perror, printf
#include <errno.h>      // for : errno
#include <string.h>     // for : strlen
#include <sys/wait.h>   // for : wait()

int main(int argc, char *arg[])
{
    int fd[2];  // Array holding the 2 file descriptor used to access the pipe
    const char *message = "This is a message!";
    int msgPipe = pipe(fd); // Creation of the pipe ( !! IMPORTANT : pipe() needs to be called before fork() !! )
    
    if (msgPipe < 0) // Return value -1 : error
    {
        printf("Creation of the pipe failed with error : %i .\n", errno);
        return 1;
    } 

    pid_t childPID;
    childPID = fork(); 

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());

            char fileDesc0[10];
            char fileDesc1[10];

            sprintf(fileDesc0, "%i", fd[0]); // We can only pass char* args, conversion from int to char*
            sprintf(fileDesc1, "%i", fd[1]); // We can only pass char* args, conversion from int to char*

            char *args[4] = {NULL};
            args[0] = "childProc/reader";
            args[1] = fileDesc0;
            args[2] = fileDesc1;
            args[3] = NULL;

            int execution = execvp("childProc/reader", args);
            
            if( execution < 0)
            {
                printf("Execution failed with error : %i .\n", errno);
                return 1;
            }
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());
            printf("Parent is sending message to child process using file descriptor %i .\n", fd[1]);

            close(fd[0]); // Close the unused reading FD (see description at the top)
            write(fd[1], message, strlen(message)+1); // the "+1" is to insert a NULL caracter otherwise this is not a CSTRING
            close(fd[1]); // Closing the writing file descriptor  
        }
    }
    else if(childPID < 0)
    {
        printf("Fork failed with error code : %i .\n", errno);
        return 1;
    }

    int status;
    wait(&status); // Wait for child process to terminate
    printf("Child process terminated, parent may now terminate .\n");

    return 0;
}