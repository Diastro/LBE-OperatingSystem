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
 * Writing to file descriptor <FD#> .
 * Reading to file descriptor <FD#> .
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

int main(int argc, char *arg[])
{
    int fd[2];  // Array holding the 2 file descriptor used to access the pipe
    char buffer[100]; // Buffer that will hold the message read from the pipre
    const char *message = "This is a message!";

    int msgPipe = pipe(fd); // Creation of the pipe

    if ( msgPipe < 0) // Return value -1 : error
    {
        printf("Creation of the pipe failed with error : %i .\n", errno);
        return 1;
    }
    else{
        // Sending through FD[1]
        printf("Writing to file descriptor %i .\n", fd[1]);
        write(fd[1], message, strlen(message)+1); // the "+1" is to insert a NULL caracter otherwise this is not a CSTRING

        // Receiving through FD[0]
        printf("Reading to file descriptor %i .\n", fd[0]);
        read(fd[0], buffer, sizeof(buffer));

        // Printing the message
        printf("Message from FD[] : \"%s\" .\n", buffer);

        close(fd[0]); // Closing the reading file descriptor
        close(fd[1]); // Closing the writing file descriptor
    }

    return 0;
}