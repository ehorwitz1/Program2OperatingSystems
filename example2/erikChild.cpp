#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
#include "queue_array.h"
#include <math.h>
using namespace std;
 
/* wrt.cpp file */

/*
class PCB{
  public:
  int pid = 0;
  int value = 0;
  int runTime = 0;
  int start_time;
  int cpu_time;
  int quantum;
  int priority;
};
*/

vector<PCB> pcbTable;
PCB cpu;  
int qTime = 0;
//QueueArray<PCB> BlockedState(100);
QueueArray<PCB> rid0(1);
QueueArray<PCB> rid1(1);
QueueArray<PCB> rid2(1);

QueueArray<PCB> ReadyState(100);


int TotalDone = 0;


void callScheduler()
{
  //If the cpu is empty
  if(cpu.pid == 0)
  {
    cout<<"CPU IS EMPTY\n";
    cpu = ReadyState.Dequeue();
    cpu.quantum = pow(2, cpu.priority);
  }
  else if(cpu.quantum == 0) //If process used its quantum
    { 
      if(cpu.cpu_time == cpu.runTime)
      {
        //Process is forever done
        cout<<"Process is done forever, load new process"<<endl;
        TotalDone++;
        cpu = ReadyState.Dequeue();
      }
      else
      { //Increase priority of process
        if(cpu.priority < 3)
        {
        cpu.priority++;
        }

        PCB newProcess = cpu;
        newProcess.quantum =  pow(2, newProcess.priority);
        ReadyState.Enqueue(newProcess, newProcess.priority);
        
        
      }
    }
  else if(cpu.cpu_time == cpu.runTime)
  {
    //Process is forever done
      cout<<"Process is done forever, load new process"<<endl;
      TotalDone++;
      cpu = ReadyState.Dequeue();
    }
  
}

void printCommand()
{
  printf("***********************************************************************\n");
  printf("The current system state is as follows:\n");
  printf("***********************************************************************\n");
  printf("CURRENT TIME: %d \n", qTime);
  printf("RUNNING PROCESS:\n");
  printf("PID\tPriority\tValue\tStart Time\tTotal CPU Time\n");
  printf("%d\t %d\t\t %d\t\t %d\t\t %d\t\t\n", cpu.pid, cpu.priority, cpu.value, cpu.start_time, cpu.cpu_time);
  
}


int main(int argc, char *argv[]) {
  int i, max = 100;
  int mcpipe2[2], num;
  char chr;

  /*
  r0:
  r1:
  r2:
  */

  //convert the parameters into the address for the pipe
  mcpipe2[0] = atoi(argv[1]);
  mcpipe2[1] = atoi(argv[2]);

  //read a character from the pipe
  read(mcpipe2[0], &chr, sizeof(char));

  while (chr != 'T') {
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

      newTable.start_time = qTime;
      cout<<"Startime is: " << newTable.start_time << "\n";
      for (int r = 0;r < 3; r++) { 
        read(mcpipe2[0], (int *)&i, sizeof(i));

       // newTable.start_time = qTime;
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

      pcbTable.push_back(newTable);
      ReadyState.Enqueue(newTable, 0);
      callScheduler();
      cout<<"Quantum: " << cpu.quantum << endl;

    } else if (chr =='B') {
      //Do we change the priority when we block
      read(mcpipe2[0], (int *)&i, sizeof(i));
      int rid = i;
      cout <<"Block current process to resource ID: " << rid<<"\n";
        PCB blockedProcess = cpu;
        cpu = PCB();

        switch(rid)
        {
            case 0:
            rid0.Enqueue(blockedProcess, 0);
            break;
            case 1:
            rid1.Enque(blockedProcess, 0);
            break;
            case 2:
            rid2.Enque(blockedProcess, 0);
            break;
        } 
        callScheduler();

      //BlockedState.Enqueue(cpu, rid);

    }else if (chr =='U') {
      //Do we change the priority when we block
      read(mcpipe2[0], (int *)&i, sizeof(i));
      int rid = i;
      cout <<"Unblock current process to resource ID: " << rid<<"\n";

        PCB unblockedProcess;
        cpu = PCB();

        switch(rid)
        {
            case 0:
            unblockedProcess = rid0.Dequeue();
            ReadyState.Enqueue(unblockedProcess, unblockedProcess.priority);
            break;
            case 1:
            unblockedProcess = rid0.Dequeue();
            ReadyState.Enqueue(unblockedProcess, unblockedProcess.priority);
            break;
            case 2:
            unblockedProcess = rid0.Dequeue();
            ReadyState.Enqueue(unblockedProcess, unblockedProcess.priority);
            break;
        } 
        callScheduler();

    } else if (chr == 'Q'){
        qTime++;

        if(cpu.pid!=0)
        {
          cpu.cpu_time++;
          cpu.quantum--;
        }

        cout<<"qTimeis: " << qTime <<"\n";
        callScheduler();

    }else if (chr == 'P'){
      /*
        cout<<"Printing characteristics\n";

        cout<<"Pid is: " << pcbTable[0].pid<<"\n";
        cout<<"Value is: " << pcbTable[0].value<<"\n";
        cout<<"RunTime is: " << pcbTable[0].runTime<<"\n";
      */
        printCommand();
        
    } else if (chr == 'C') {
      
      //Read the command to execute
      read(mcpipe2[0], (char *)&chr, sizeof(char));
      char command = chr;
      cout<<"This is Command "<< command <<"\n";

      //Read in the value to change the current process
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
      qTime++;
      cpu.cpu_time++;
      cpu.quantum--;
      callScheduler();
      
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



