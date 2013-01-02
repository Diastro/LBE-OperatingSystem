/**
 * File             : 01pipe.cpp
 * Date of creation : January 1 2013
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * Introduction to unnamed pipe. 
 *
 *      write() --> fd[1] -- |======= PIPE =======| -- fd[0] --> read() 
 *
 * Output :
 * -----------------------------------
 * Writing to file descriptor 4 .
 * Reading to file descriptor 3 .
 * Message from FD[] : "This is a message!" .
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
#include <stdlib.h>    // for : atoi

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
    printf("Reading to file descriptor %i .\n", fd[0]);
    read(fd[0], buffer, sizeof(buffer));

    // Printing the message
    printf("Message from FD[] : \"%s\" .\n", buffer);

    close(fd[0]); // Closing the reading file descriptor  

    return 0;
}