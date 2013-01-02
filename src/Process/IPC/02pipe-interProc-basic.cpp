/**
 * File             : 02pipe-interProc-basic.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to unnamed pipe between 2 process. The parent process will write in the pipe and the child
 * will read from the pipe. Each process has to close the file descriptor that it won't use as follow:
 *
 * ParentProc (writing):
 *                          open                               close                                             
 *              write() --> fd[1] -- |======= PIPE#1 =======| -- fd[0] --> read() 
 *
 * ChildProc (reading):
 *                          close                              open                                             
 *              write() --> fd[1] -- |======= PIPE#1 =======| -- fd[0] --> read() 
 *
 * Output :
 * -----------------------------------
 * Parent Process ID : <PID-Parent> .
 * Parent is sending message to child process .
 * Child Process ID : <PID-Child> .
 * Child Process receiving message from parent : "This is a message!" .
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
    char buffer[100]; // Buffer that will hold the message read from the pipe
    const char *message = "This is a message!";
    int msgPipe = pipe(fd); // Creation of the pipe ( !! IMPORTANT : pipe() needs to be called before fork() !! )

    if ( msgPipe < 0) // Return value -1 : error
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

            close(fd[1]); // Close the unused FD (see description at the top)
            int byteRead = read( fd[0], buffer, sizeof(buffer));
            printf("Child Process receiving message from parent : \"%s\" .\n", buffer);

            return 0;
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());
            printf("Parent is sending message to child process .\n", getpid());

            close(fd[0]); // Close the unused FD (see description at the top)
            write(fd[1], message, strlen(message)+1); // the "+1" is to insert a NULL caracter otherwise this is not a CSTRING
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