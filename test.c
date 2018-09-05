//this is a series of tests for each individual part of the program for errors
///they were combined into one for quick checking
#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"config.h"
#include"component.h"

void output(char *s);
int randNumber(int min, int max);
//define filenames
#define LOGFILE "./testlog.txt"
#define CONFIG_FILE "./config.txt"
//this function returns a random number between a min and max
int randNumber(int min, int max){
  return min+(rand() % (max+1));
}

void output(char *s){

  //open log file
  FILE *file = fopen(LOGFILE, "a");

  //if file could not be opened
  if (file == NULL){
    //error message
    puts("Error: Could not open log file");
    exit(-1);
  }
  //else file is open
  else{
    //print message to console
    printf ("%s\n", s);
    //write to log file
    fprintf(file, "%s\n", s);
  }

  //close file
  fclose(file);
}

int main(){

  puts("*************Log test***************\n Check testlog.txt for similar output\n");
  output("The quick brown fox");
  output("jumped\n over the\n\n\nlazy dog.");

  puts("\n************testing config.h*************\n check config.text for correct results");
  //get config
  config *myConfig = get_config(CONFIG_FILE);
  //print variables
  printf("INIT: %d\t\t FIN: %d\n", myConfig->INIT_TIME, myConfig->FIN_TIME);
  printf("CPU MIN: %d\t CPU MAX: %d\nCPU QUIT PROB: %d\n", myConfig->CPU_MIN, myConfig->CPU_MAX, myConfig->QUIT_PROB);
  printf("DISK1 MIN: %d\t DISK1 MAX: %d\n", myConfig->DISK1_MIN, myConfig->DISK1_MAX);
  printf("DISK2 MIN: %d\t DISK2 MAX: %d\n", myConfig->DISK2_MIN, myConfig->DISK2_MAX);
  //free memory
  free(myConfig);

  puts("\n***********testing queue.h****************\n");
  //create queue
  queue *q = createQueue();
  //add nodes, and print at each step
  enQueue(q, 2);
  printQueue(q);
  enQueue(q, 299593);
  printQueue(q);
  enQueue(q, -4566543);
  printQueue(q);
  enQueue(q, 2211111122);
  printQueue(q);
  //remove nodes from queue, print queue at each step
  printf("Removed %d from queue\n", deQueue(q)->key);
  printQueue(q);
  printf("Removed %d from queue\n", deQueue(q)->key);
  printQueue(q);
  printf("Removed %d from queue\n", deQueue(q)->key);
  printQueue(q);
  printf("Removed %d from queue\n", deQueue(q)->key);
  printQueue(q);
  //intentionally tying to remove a node from an empty queue
  deQueue(q);
  deQueue(q);
  printQueue(q);
  free(q);


  puts("\n**************Testing component.h**************");
  puts("\n*1: moving around nodes in queue*\n");
  //getting 2 component structs
  component *cpu = get_component();
  component *disk = get_component();

  //add nodes to QUEUE
  push(cpu, 5);
  push(cpu, 6);
  push(cpu, 9);
  push(cpu, 2);
  push(cpu, 1);
  push(disk, 3);

  //display queues
  printf("CPU:");
  printQueue(cpu->QUEUE);
  printf("DISK:");
  printQueue(disk->QUEUE);

  //move nodes from cpu to disk
  while(!Empty(cpu->QUEUE)){
    push(disk, pop(cpu));
  }

  //display queues
  printf("***\nCPU:");
  printQueue(cpu->QUEUE);
  printf("DISK:");
  printQueue(disk->QUEUE);

  //move nodes from disk to cpu
  while(!Empty(disk->QUEUE)){
    push(cpu, pop(disk));
  }

  //display queues
  printf("***\nCPU:");
  printQueue(cpu->QUEUE);
  printf("DISK:");
  printQueue(disk->QUEUE);

  puts("\n*2: test wait timer*\n");

  //loop 5 times
  for (int i = 0; i < 5; i++){
    //give random wait times
    cpu->WAIT_TIME = randNumber(1, 100);
    disk->WAIT_TIME = randNumber(1, 100);
    //print them out
    printf("CPU WAIT: %d\nDISK WAIT: %d\n", cpu->WAIT_TIME, disk->WAIT_TIME);
    //test for loop timer
    for (int j = 0; j<100; j++){
      if (j == cpu->WAIT_TIME)
        printf("%d: CPU\n", j);
      if (j == disk->WAIT_TIME)
        printf("%d: DISK\n", j);
    }
  }

}
