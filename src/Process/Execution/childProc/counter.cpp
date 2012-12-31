/**
 * File             : counter.cpp
 * Date of creation : December 31 2012
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * This file will be use as a chil process for the EXECUTION section of the process example.
 * The containning folder already holds the executable for this file. If you wish to rebuild
 * it, use the command :
 * 
 *     gcc counter.cpp -o counter
 *
 * To execute the ouput file in a console use :
 *     ./counter <arg-1>
 *
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./counter <arg-1>
 * 
 * Where <arg-1> is last number to count to.
 * ex : ./counter 5
 *
 * Output :
 * -----------------------------------
 * ChildProc is counting: 1 .
 * ChildProc is counting: 2 .
 * ChildProc is counting: 3 .
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 * - http://linux.die.net/man/3/execl
 *
 * Output :
 * -----------------------------------

 * -----------------------------------
 */

#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>     // for : atoi

int main(int argc, char *arg[])
{
    // int argc     : holds the number of argument present. By default the first argument (arg[0]) is the name of the file
    // char *arg[]  : holds arguments
    
    if(argc < 2){ // Check to make sure the user put argument before executing the script
        printf("Missing argument, exiting .\n");
        return 1;
    }

    int count = 1;
    int maxCount = atoi(arg[1]); // Converts the string argument into an integer

    while(count <= maxCount){ // ChildProc is doing work
        printf("ChildProc is counting: %i .\n", count);
        count++;
    }

    return 0;
}