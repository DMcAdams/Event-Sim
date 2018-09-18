//this is a series of tests for each individual part of the program for errors
///they were combined into one for quick checking
#include<stdio.h>
#include<stdlib.h>
#include"./headers/queue.h"
#include"./headers/config.h"
#include"./headers/component.h"


void output(char *s);
int randNumber(int min, int max);
//define filenames
#define LOGFILE "./testlog.txt"
#define CONFIG_FILE "./config.txt"
//used for component status
#define RUNNING 1
#define IDLE 0


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

//this function simulates the CPU
void sim_cpu(config *myConfig, component *cpu, component *disk1, component *disk2, int currentTime){

  //used for sending jobs to a disk
  int diskNum;
  int temp;

  //used for logging output
  char string[BUFF_SIZE];

  //get current status for CPU
  switch (cpu->STATUS) {

    //if cpu is IDLE
    case IDLE:
      //get new wait time
      cpu->WAIT_TIME = currentTime + randNumber(myConfig->CPU_MIN, myConfig->CPU_MAX);
      //print out arrival message
      sprintf(string,"%d\tJob %d: Arrived at CPU", currentTime, cpu->QUEUE->front->key);
      output(string);
      //update status
      cpu->STATUS = RUNNING;
      break;

    //CPU is running
    case RUNNING:
      //remove job from CPU queue
      temp = pop(cpu);

      //check if job is finished (random % chance based on QUIT_PROB)
      if (myConfig->QUIT_PROB >= randNumber(0, 100)){
        //log message
        sprintf(string, "%d\tJob %d: Finished.", currentTime, temp);
        output(string);
        //add to PROCESSED and COMPLETED counters
        cpu->COMPLETED ++;
        cpu->PROCESSED ++;
        //update cpu status and finish
        cpu->STATUS = IDLE;
        return;
      }

      //send job to DISK with least amount of jobs
      if (disk1->QUEUE->count < disk2->QUEUE->count){
        push(disk1, temp);
        diskNum = 1;
      }
      else if (disk1->QUEUE->count > disk2->QUEUE->count){
        push(disk2, temp);
        diskNum = 2;
      }
      //if same amount of jobs, pick one at random
      else{
        int num = randNumber(0,100);
        if (num>=50){
          push(disk1, temp);
          diskNum = 1;
        }
        else{
          push(disk2, temp);
          diskNum = 2;
        }
      }
      //print message
      sprintf(string,"%d\tJob %d: Sent to DISK %d from CPU", currentTime, temp, diskNum);
      output(string);
      //add to completed Counter
      //set CPU to IDLE
      cpu->PROCESSED ++;
      cpu->STATUS = IDLE;
      break;
  }
}

//this function simulates a DISK
void sim_disk(component *disk, component *cpu, int currentTime, int DISK_MIN, int DISK_MAX, int diskNum){
  int temp;
  //for logging output
  char string[BUFF_SIZE];

  //get DISK status
  switch (disk->STATUS) {

    //disk is IDLE
    case IDLE:
      //get new wait time
      disk->WAIT_TIME = currentTime + randNumber(DISK_MIN, DISK_MAX);
      //output arrival message for testing
      sprintf(string, "%d\tJob %d: Arrived at DISK %d", currentTime, disk->QUEUE->front->key, diskNum);
      output(string);
      //set disk to RUNNING
      disk->STATUS = RUNNING;

    break;

    //disk is RUNNING
    case RUNNING:
      //remove job from DISK queue
      temp = pop(disk);
      //put job back into job queue
      push(cpu, temp);
      //print message
      sprintf(string, "%d\tJob %d: I/O finished on DISK %d, sent back to job queue", currentTime, temp, diskNum);
      output(string);
      //add one to completion counter
      disk->PROCESSED++;
      //set disk status to idle
      disk->STATUS = IDLE;
      break;
  }
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
  if (Empty(q))
    puts("empty");
  else
    puts("not empty");
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

  //empty cpu queue for later test
  while(!Empty(cpu->QUEUE)){
    int temp = pop(cpu);
  }

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

  puts("\n**************Testing sim_cpu()**************");
  //create disk2
  //cpu and disk already made in earlier tests
  component *disk2 = get_component();
  //reset wait timers from pervious tests
  cpu->WAIT_TIME = 0;
  disk->WAIT_TIME = 0;

  //add 30 jobs to the cpu
  for (int i = 1; i <= 30; i++){
    push(cpu, i);
  }

  puts("\n Checking contents of queues");
  puts("CPU:");
  printQueue(cpu->QUEUE);
  puts("Disk 1:");
  printQueue(disk->QUEUE);
  puts("DISK 2:");
  printQueue(disk2->QUEUE);

  //run sim_CPU for 1000 ticks
  for (int i = 0; i < 1000; i++){
    //if cpu is ready and has pending job
    if (cpu->WAIT_TIME < i && !Empty(cpu->QUEUE)){
      //i takes the place of current time
      sim_cpu(myConfig, cpu, disk, disk2, i);
    }
  }

  puts("\nCPU:");
  printQueue(cpu->QUEUE);
  puts("Disk 1:");
  printQueue(disk->QUEUE);
  puts("DISK 2:");
  printQueue(disk2->QUEUE);

  puts("\n**************Testing sim_disk()**************");

  puts("Disk 1:");
  //run sim_disk for 1000 ticks on Disk 1
  for (int i = 0; i < 1000; i++){
    //if disk is ready and has pending job
    if (disk->WAIT_TIME < i && !Empty(disk->QUEUE)){
      //i takes the place of currentTime
      sim_disk(disk, cpu, i, myConfig->DISK1_MIN, myConfig->DISK1_MAX, 1);
    }
  }
  //output all queues
  puts("\nCPU Queue:");
  printQueue(cpu->QUEUE);
  puts("Disk 1 Queue");
  printQueue(disk->QUEUE);
  puts("Disk 2 Queue:");
  printQueue(disk2->QUEUE);

  //test disk 2
  puts("\nDisk 2:");
  //run sim_disk for 1000 ticks on Disk 2
  for (int i = 0; i < 1000; i++){
    //if disk2 is ready and has pending job
    if (disk2->WAIT_TIME < i && !Empty(disk2->QUEUE)){
      //i takes the place of currentTime
      sim_disk(disk2, cpu, i, myConfig->DISK2_MIN, myConfig->DISK2_MAX, 2);
    }
  }
  //output all queues
  puts("\nCPU Queue:");
  printQueue(cpu->QUEUE);
  puts("Disk 1 Queue:");
  printQueue(disk->QUEUE);
  puts("Disk 2 Queue:");
  printQueue(disk2->QUEUE);

}
