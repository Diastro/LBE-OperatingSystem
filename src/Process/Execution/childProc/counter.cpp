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
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./counter <arg-1> <arg-2>
 * 
 *     - Where <arg-1> is the name of the object you're counting.
 *     - Where <arg-2> is last number to count to. * 
 *     ex : ./counter cars 3
 *
 * Output :
 * -----------------------------------
 * Counting : 1 cars .
 * Counting : 2 cars .
 * Counting : 3 cars .
 * -----------------------------------
 * 
 * References :
 * - http://www.die.net
 *
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
    
    if(argc < 3){ // Check to make sure the user put argument before executing the script
        printf("Missing argument, exiting .\n");
        return 1;
    }

    int count = 1;
    char *objectName = arg[1];
    int maxCount = atoi(arg[2]); // Converts the string argument into an integer

    while(count <= maxCount){ // ChildProc is doing work
        printf("Counting : %i %s .\n", count, objectName);
        count++;
    }

    return 0;
}