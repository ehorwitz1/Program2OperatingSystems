#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "queue_array.h"
using namespace std;
 
/* wrt.cpp file */

class PCB{
  public:
  int pid = 0;
  int value = 0;
  int runTime = 0;
  int start_time =0;
  int run_tme = 0;
  int cpu_time = 0;
};

int main(int argc, char *argv[]) {
  int i, max = 100;
  int mcpipe2[2], num;
  char chr;

  vector<PCB> tableVector;
  QueueArray<PCB> BlockedState;
  QueueArray<PCB> ReadyState;


  PCB cpu;

  char butt;

  int Sarray[3];

  int Time = 0;

  QueueArray<PCB> Qarray(20);
    
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
    } else if (chr == 'S') {
      //read a number from the pipe
      cout<<"S values here\n";
      PCB newTable;

      for (int r = 0;r < 3; r++) { 
        read(mcpipe2[0], (int *)&i, sizeof(i));
        Sarray[r] = i;
        cout <<"Sarray at "<< r << "is "<< Sarray[r] << "\n";
        switch(r)
        {
            case 0:
            newTable.pid = i;
            cout<<"Pid is: " << newTable.pid << "\n";
            break;
            case 1:
            newTable.value = i;
            cout<<"value is: " << newTable.value << "\n";
            break;
            case 2:
            newTable.runTime = i;
            cout<<"runTime is: " << newTable.runTime << "\n";
            break;
        } 

      }
      tableVector.push_back(newTable);
      //Qarray.Enqueue(newTable, newTable.pid);
    } else if (chr =='B') {
      cout <<"Wrt: Bye!\n";
    } else if (chr == 'Q'){
        Time++;
        cout<<"Time is: " << Time<<"\n";
    }else if (chr == 'V'){
        cout<<"Printing characteristics\n";
        //sTable printTable = tableVector[0];
        PCB *printTable = Qarray.Qstate(0);
        cout<<"Pid is: " << tableVector[0].pid<<"\n";
        cout<<"Value is: " << tableVector[0].value<<"\n";
        cout<<"RunTime is: " << tableVector[0].runTime<<"\n";
        
    } else if (chr == 'C') {
      //read a number from the pipe
      read(mcpipe2[0], (char *)&chr, sizeof(char));
      char command = chr;
      cout<<"This is Command "<< command <<"\n";
      read(mcpipe2[0], (int *)&i, sizeof(i));
      int num = i;
      cout<<"This is Num "<< num <<"\n";

      switch(command)
        {
            case 'A':
            cpu.value = cpu.value + num;
            cout<<"Added: " << num << "\n";
            break;
            case 'S':
            cpu.value = cpu.value - num;
            cout<<"Subtracted: " << num << "\n";
            break;
            case 'M':
            cpu.value = cpu.value * num;
            cout<<"Multiplied: " << num << "\n";
            break;
            case 'D':
            cpu.value = cpu.value / num;
            cout<<"Divided: " << num << "\n";
            break;
        } 


      
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

