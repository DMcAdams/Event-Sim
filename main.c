#include<stdid>
#include<stdlib>
#include"queue.h"

int main(){
  //create job queue
  struct queue *job_queue = createQueue();
  //tracks number of jobs
  int job_count = 0;
}


//this function simulates the CPU
void sim_cpu(){
  //pseudocode

  /*
  if NOT RUNNING:
    get wait timer
    set status to running
  fi

  if RUNNING:
    Remove next job in CPU queue
    if job is done(rand chance):
      remove job from queue
    else
      place job in least used disk queue
    set status to NOT RUNNING
  fi
  */
}
//this function simulates a DISK
void sim_disk(){
  ///pseudocode

  /*
  if NOT RUNNING:
    get wait timer
    set status to running

  if RUNNING:
    Remove next job in disk queue
    place job in least used disk queue
    set status to NOT RUNNING
  */

}

//this function returns a random number between a min and max
int randNumber(int min, int max){
  return min+(rand() % (max+1));
}
