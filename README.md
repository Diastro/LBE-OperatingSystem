LBE-OperatingSystem
===================

Learn by example : Operating system

WORK IN PROGRESS.

##Execution
To run any code example in a Linux environment (I use ubuntu) do the following :

1) Compile any .cpp file :

    gcc 01fork.cpp -o output
  
2) Execute the corresponding output file :

    ./output
    
##Content

### Process

* Basics
    * **01fork.cpp** - How to fork
    * **02waitpid-basic.cpp** - Wait for a given process to terminate
    * **02waitpif-elaborated.cpp** - Wait for a given process to terminate and retrive signal or exit value
    * **03waitpid-nonBlocking.cpp** - Wait for a given process to terminate without blocking the parent process
    * **04wait.cpp** - Wait for all process to terminate
* Execution
    * Item 1
    * Item 2
* IPC
    * Item 1
    * Item 2

### Threads

* Basics
    * Item 1
    * Item 2
* Synchonization
    * Item 1
    * Item 2
    
##References
- [Die.net - Linux Doc](http://www.die.net)
- [A short introduction to operating systems, by Mark Burgess](http://www.iu.hio.no/~mark/os/os.html)
- [Google's CPP coding guideline](http://google-styleguide.googlecode.com/svn/trunk/cppguide.xml)
