#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"config.h"
#include"component.h"

void sim_cpu(config *myConfig, component *cpu, component *disk1, component *disk2, int currentTime);
void output(char *s);
int randNumber(int min, int max);
//define filenames
#define LOGFILE "./log.txt"
#define CONFIG_FILE "./config.txt"
//define hardware status
#define IDLE 0
#define RUNNING 1

int main(){

  //set up simulated components
  component *cpu = get_component();
  component *disk1 = get_component();
  component *disk2 = get_component();

  //get config info from config.txt
  config *myConfig = get_config(CONFIG_FILE);
  //set current time to starting time specified in config
  int currentTime = myConfig->INIT_TIME;

  //create job queue
  queue *job_queue = createQueue();
  //tracks number of jobs
  int job_count = 0;

  output("************SIMULATION START************");
  //main loop, each tick on the simulated clock checks the CPU and both disks.
  while (currentTime < myConfig->FIN_TIME){
    //make sure that there is always an available job
    if (job_queue->count == 0){
      //increment job counter
      job_count++;
      //add new job to queue
      enQueue(job_queue, job_count);

    }
    //make sure that CPU has at least 1 job in queue
    if (cpu->QUEUE->count == 0){
      //take a job from the job_queue
      enQueue(cpu->QUEUE, deQueue(job_queue)->key);
    }

    //if cpu is free and has a job in queue
        if (cpu->WAIT_TIME < currentTime && cpu->QUEUE->front != NULL) {
            //simulates the CPU, gets it's current wait time
            sim_cpu(myConfig, cpu, disk1, disk2, currentTime);
        }

    currentTime++;
  }
  //sim end
  output("************SIMULATION END************");
}


//this function simulates the CPU
void sim_cpu(config *myConfig, component *cpu, component *disk1, component *disk2, int currentTime){

  //used for sending jobs to a disk
  int diskNum;
  node *temp;

  //get current status for CPU
  switch (cpu->STATUS) {

    //if cpu is IDLE
    case IDLE:
      //get new wait time
      cpu->WAIT_TIME = currentTime + randNumber(myConfig->CPU_MIN, myConfig->CPU_MAX);
      //print out arrival message
      printf("%d\tJob %d: Arrived at CPU\n", currentTime, cpu->QUEUE->front->key);
      //update status
      cpu->STATUS = RUNNING;
      break;

    //CPU is running
    case RUNNING:
      //remove job from CPU queue
      temp = deQueue(cpu->QUEUE);
      //send job to DISK with least amount of jobs
      if (disk1->QUEUE->count < disk2->QUEUE->count){
        enQueue(disk1->QUEUE, temp->key);
        diskNum = 1;
      }
      else if (disk1->QUEUE->count > disk2->QUEUE->count){
        enQueue(disk2->QUEUE, temp->key);
        diskNum = 2;
      }
      //if same amount of jobs, pick one at random
      else{
        int num = randNumber(0,100);
        if (num>50){
          enQueue(disk1->QUEUE, temp->key);
          diskNum = 1;
        }
        else{
          enQueue(disk2->QUEUE, temp->key);
          diskNum = 2;
        }
      }
      //print message
      printf("%d\tJob %d: Set to DISK %d from CPU\n", currentTime, temp->key, diskNum);
      //set CPU to IDLE
      cpu->STATUS = IDLE;
      break;
  }
}
//this function simulates a DISK
void sim_disk(){
  ///pseudocode

  /*
  if NOT RUNNING:
    get wait timer
    set status to running
  fi

  if RUNNING:
    Remove next job in disk queue
    place job in least used disk queue
    set status to NOT RUNNING
  fi
  */

}

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
