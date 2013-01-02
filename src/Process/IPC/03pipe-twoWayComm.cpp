/**
 * File             : 03twoWayComm.cpp
 * Date of creation : January 2 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to unnamed pipe between 2 process (two way communication).
 *
 * PIPE # 1 :
 * ParentProc (writing):
 *                          open                                 close                                             
 *              write() --> fd[1] -- |======= PIPE#1 =======| -- fd[0] --> read() 
 *
 * ChildProc (reading):
 *                          close                                open                                             
 *              write() --> fd[1] -- |======= PIPE#1 =======| -- fd[0] --> read()
 *              
 * -----------------------------------
 *
 * PIPE # 2 :
 * ParentProc (reading):
 *                          close                                open                                             
 *              write() --> fd[1] -- |======= PIPE#2 =======| -- fd[0] --> read() 
 *
 * ChildProc (writing):
 *                          open                                 close                                             
 *              write() --> fd[1] -- |======= PIPE#2 =======| -- fd[0] --> read()
 *              
 * -----------------------------------
 *
 * Output :
 * -----------------------------------
 * Parent Process ID : <PID-Parent> .
 * Child Process ID : <PID-Child> .
 * Child Process receiving message from parent : "New message from parent!" .
 * Parent Process receiving message from child : "Message received!" .
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
    int fdPipe1[2];  // Array holding the 2 file descriptor used to access the pipe#1
    int fdPipe2[2];  // Array holding the 2 file descriptor used to access the pipe#2

    int pipe1 = pipe(fdPipe1); // Creation of the pipe ( !! IMPORTANT : pipe() needs to be called before fork() !! )
    int pipe2 = pipe(fdPipe2); // Creation of the pipe ( !! IMPORTANT : pipe() needs to be called before fork() !! )

    if ((pipe1 < 0) || (pipe2 < 0)) // Return value -1 : error
    {
        printf("Creation of one of the pipe failed with error : %i .\n", errno);
        return 1;
    } 

    const char *messageToChild = "New message from parent!";
    const char *messageToParent = "Message received!";
    char bufferChild[100]; // Buffer that will hold the message read from the pipe for the child process
    char bufferParent[100]; // Buffer that will hold the message read from the pipe for the parent process

    pid_t childPID;
    childPID = fork(); 

    if(childPID >= 0)
    {
        if(childPID == 0) // Code executed in the child process
        {
            printf("Child Process ID : %i .\n", getpid());

            close(fdPipe1[1]); // Good practice : closing the unused end of the pipe
            read(fdPipe1[0], bufferChild, sizeof(bufferChild));
            printf("Child Process receiving message from parent : \"%s\" .\n", bufferChild);

            close(fdPipe2[0]); // Good practice : closing the unused end of the pipe
            write(fdPipe2[1], messageToParent, strlen(messageToParent)+1); // the "+1" is to insert a NULL caracter otherwise this is not a CSTRING
            
            // CleanUp
            close(fdPipe1[0]);
            close(fdPipe2[1]);

            return 0;
        }
        else // Code executed in the parent process
        {
            printf("Parent Process ID : %i .\n", getpid());

            close(fdPipe1[0]); // Good practice : closing the unused end of the pipe
            write(fdPipe1[1], messageToChild, strlen(messageToChild)+1); // the "+1" is to insert a NULL caracter otherwise this is not a CSTRING
            
            close(fdPipe2[1]); // Good practice : closing the unused end of the pipe
            read(fdPipe2[0], bufferParent, sizeof(bufferParent));
            printf("Parent Process receiving message from child : \"%s\" .\n", bufferParent);

            // CleanUp
            close(fdPipe1[1]);
            close(fdPipe2[0]);
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