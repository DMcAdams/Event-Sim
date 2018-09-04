#include<stdio.h>
#include<stdlib.h>
#include"queue.h"

void output(char *s);
//define filenames
#define LOGFILE "./log.txt"

int main(){
  //testing log file
  output("The quick brown fox");
  output("jumped over the lazy dog");
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
