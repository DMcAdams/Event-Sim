/*==============================================================================
 |       Author:  Darrin McAdams
 |         Date:  September 4th, 2018
 |  Description:  This header file provides structs that hold a queue and
 |                  status info for simulated hardware.
 *============================================================================*/


#include"queue.h"
#ifndef COMPONENT_H
#define COMPONENT_H

//struct for hardware components
typedef struct component{
  struct queue *QUEUE;
  int WAIT_TIME;
  int STATUS;
  long long SIZE;
  long MOST_JOBS;
  int PROCESSED;
  int COMPLETED;
} component;

//function to initialize component struct
component *get_component(){
  //create component in memory
  component *temp = malloc(sizeof(struct component));
  //set variables
  temp->QUEUE = createQueue();
  temp->WAIT_TIME = 0;
  temp->STATUS = 0;
  temp->SIZE = 0;
  temp->MOST_JOBS = 0;
  temp->PROCESSED = 0;
  temp->COMPLETED = 0;
  //return
  return temp;
}

//push new items into component's queue
void push(component *temp, int key){
  enQueue(temp->QUEUE, key);
}

//remove next element from the queue, and return it's key
int pop(component *temp){
  //get node
  node *n = deQueue(temp->QUEUE);
  //get value of node
  int key = n->key;
  //free memory
  free(n);
  return key;
}
#endif
