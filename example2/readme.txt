
There are two files. The program in master.cpp creates a wrt process.
The master reads from the command line and sends the information to wrt.
The input can be H X where X is a number, B, and P. 
H X: the clients say Hi X number of times
B: the client says Bye one time
P: client exits

Both the master and client will write to the screen.  Also there is a
sleep call in the master for 1 second.

Compile each file separately as follows:

g++ -o master master.cpp
g++ -o wrt wrt.cpp

#you can take in the command manually
./master

#There is an input file is called: input
#or redirect a file of commands
./master <input

Feel free to "play" with the program.  You may want to comment out the 
sleep call in the master see the output faster.
