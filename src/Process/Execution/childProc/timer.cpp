/**
 * File             : timer.cpp
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
 *     gcc timer.cpp -o timer
 *
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./timer <arg-1>
 * 
 *     - Where <arg-1> is time (in second) to count up to.
 *     ex : ./timer 3
 *
 * Output :
 * -----------------------------------
 * ChildProc timer countdown: 1 second(s).
 * ChildProc timer countdown: 2 second(s).
 * ChildProc timer countdown: 3 second(s).
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
    
    if(argc < 2){ // Check to make sure the user put argument before executing the script
        printf("Missing argument, exiting .\n");
        return 1;
    }

    int count = 1;
    int maxCount = atoi(arg[1]); // Converts the string argument into an integer

    while(count <= maxCount){ // ChildProc is doing work
        printf("ChildProc timer countdown: %i second(s).\n", count);
        sleep(1);
        count++;
    }

    return 0;
}