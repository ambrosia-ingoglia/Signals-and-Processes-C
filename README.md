# Signals-and-Processes-C

In this assignment I worked with signals and processes. It was designed to help get a better understanding of how to write code with creates processes and having them communicate with each other through signals.


 Wrote a program that blocks all signals
        saved this program in blocker.c/cpp
        had the program print to stdout a message saying all the signals are blocked
        had it unblock the signals after sleeping for 3 seconds.
        had it print to stdout when the signals are no longer blocked
Wriote a program which displays all supported signals on your computer to stdout
        saved the program in signalsavailable.c/cpp
Wrote a program saved in children.c/cpp which creates a child process and does the following
        created a child process using fork()
        the child
            sleeps for 3 seconds
            runs a 'blocker' program
            gets and prints to stdout the status of the 'blocker' program
            prints to stdout the pid of the 'blocker' program
            tests and prints to stdout how the 'blocker' program terminated
                normally
                abnormally
            The output identifies the child output with 'Child:' for each output.
        the parent
            prints to stdout the pid of the child
            gets and prints to stdout the status of the child
            waits for the child to complete
            tests and prints to stdout how the child process terminated
                normally
                abnormally
            The output identifies the parent output with 'Parent:' for each output.
        ran the 'children' program using the 'blocker' program as an argument
            All the output of these programs are saved in a readme.txt file
