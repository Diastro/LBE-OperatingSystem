/**
 * File             : reader.cpp
 * Date of creation : January 1 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * This file will be use as a chil process for the IPC section of the process examples.
 * The containning folder already holds the executable for this file. If you wish to rebuild
 * it, use the command :
 * 
 *     gcc reader.cpp -o reader
 *
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./reader <arg-1> <arg-2>
 * 
 *     - Where <arg-1> is file descriptor from which we will read.   -  fd[0]
 *     - Where <arg-2> is file descriptor from which we could write. -  fd[1]
 *     ex : ./reader fd[0] fd[1]
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
#include <stdlib.h>     // for : atoi

int main(int argc, char *arg[])
{
    if(argc < 3) // Check to make sure the user put argument before executing the script
    {
        printf("Missing argument... \n");
        printf("Exiting .\n");
        return 1;
    }

    char buffer[300];
    int fd[2];
    fd[0] = atoi(arg[1]);
    fd[1] = atoi(arg[2]);

    close(fd[1]); // Closing the writing file descriptor
    
    // Receiving through FD[0]
    printf("Child process is reading from file descriptor %i .\n", fd[0]);
    read(fd[0], buffer, sizeof(buffer));

    // Printing the message
    printf("Child process received message : \"%s\" .\n", buffer);

    close(fd[0]); // Closing the reading file descriptor  

    return 0;
}