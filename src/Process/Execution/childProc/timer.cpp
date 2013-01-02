/**
 * File             : timer.cpp
 * Date of creation : December 31 2012
 * Author           : David Albertson
 * Twitter          : @DavidAlbertson
 * Website          : www.dalbertson.com
 *
 * Description : 
 * This file will be use as a child process for the EXECUTION section.
 * The containing folder already holds the executable for this file. If you wish to rebuild
 * it, use the command :
 * 
 *     gcc timer.cpp -o timer
 *
 * Execution :  
 * To execute the ouput file in a console use :
 *     ./timer <arg-1>
 * 
 *     - Where <arg-1> is the time (in second) to count up to.
 *     ex : ./timer 3
 *
 * Output :
 * -----------------------------------
 * Timer count: 1 second(s).
 * Timer count: 2 second(s).
 * Timer count: 3 second(s).
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
    
    if(argc < 2) // Check to make sure the user put argument before executing the script
    {
        printf("Missing argument, exiting .\n");
        return 1;
    }

    int count = 1;
    int maxCount = atoi(arg[1]); // Converts the string arg[2] into an integer

    while(count <= maxCount){ // Timer is doing work
        printf("Timer count: %i second(s).\n", count);
        sleep(1);
        count++;
    }

    return 0;
}
