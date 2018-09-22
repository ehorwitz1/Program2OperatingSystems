/*
  Here is some example code for Program 1.  You don't have to use any of
  it, but if you are having trouble, it might get you started.
  The etype used through this is the template class your need to create
  in this class, etype means Example TYPE
*/
#ifndef QUEUEARRAY_H
#define QUEUEARRAY_H

#include <iostream>
#include <cstdlib>  //This is for the exit command.

#include <queue>

using namespace std;

/*
 *  In the class below, it declares a "queue<etype>" array.     
 *  you don't need to use the STL queue (but you can), choose a data structure
 * that you think works.   If you choose to write you own queue class, then 
 * it has better follow all the requirements to a queue, to include the O time
 * minimum timing requirements of c++
*/

//Talked with Jacob Claytor


template <class etype>
class QueueArray
{
  public:
    QueueArray(int);
    ~QueueArray()
    {
      delete[] array;
    }

    int Asize()
    {
      return size;
    } 

    etype Dequeue()
    {
      for (int i = 0; i < Asize(); i++)
      {
        if(Qsize(i) != 0)
        {
          etype temp = array[i].front();
          array[i].pop();
          return temp;
        }
      }
      return 0;
    }

    int Enqueue(const etype &item,const int index)
    {
      if(index > Asize())
      {
        return -1;
      }
      else
      {
        array[index].push(item);
        return 1;
      }
      return 0;
    }

    int QAsize()
    {
      int total = 0;
      for(int i = 0; i < Asize(); i++)
      {
        total += Qsize(i);
      }
      return total;
    } 
    
    int Qsize(int index) 
    {
      if(index > Asize())
      {
        return -1;
      }
      else
      {
        return array[index].size();
      }
    }

    etype* Qstate(int index)
    {
      if(index >= Asize() || index < 0)
      {
        return NULL;
      }
      else
      {
        queue<etype> tempQueue = array[index]; //Temp Queue that we will use to return
        etype* arrayToReturn = new etype[Qsize(index)]; //Temp array we will actualyl return

        for(int i =0; i < Qsize(index); i ++)
        {
          arrayToReturn[i] = tempQueue.front();
          tempQueue.pop();
        }
        return arrayToReturn;
      }

    }

  private:
    int size;      //size of the array
    queue<etype>* array;   //the array of queues.  It must be an array (NO not a vector)
    int totalItems; //total number of items stored in the queues
};

//Constructor for the queue array.  It sets the default size
//to 10, initializes the private variables size and totalItems
template <class etype>
QueueArray<etype>::QueueArray(int sz = 10):size(sz),totalItems(0)
{
  array = new queue<etype>[size];
  if( array == NULL)
  {
    cout << "Not enough memory to create the array" << endl;
    exit(-1);
  }
}

#endif