#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
using namespace std;
 
/* wrt.cpp file */

int main(int argc, char *argv[]) {
  int i, max = 100;
  int mcpipe2[2], num;
  char chr;
 
  //convert the parameters into the address for the pipe
  mcpipe2[0] = atoi(argv[1]);
  mcpipe2[1] = atoi(argv[2]);

  //read a character from the pipe
  read(mcpipe2[0], &chr, sizeof(char));

  while (chr != 'P') {
    if (chr == 'H') {
      //read a number from the pipe
      read(mcpipe2[0], (int *)&i, sizeof(i));
      for (;i!=0; --i) { 
        cout <<"Wrt: Hi!\n";
      }
    } else if (chr =='B') {
      cout <<"Wrt: Bye!\n";
    }
   //read a character from the pipe
    read(mcpipe2[0], &chr, sizeof(char));
  }
  //close down the pipe 
  close(mcpipe2[0]);
  close(mcpipe2[1]);
  //return with a 2, so the parent receive the status message of 2
  // note the number can not greater then 255.
  return 2;
}

