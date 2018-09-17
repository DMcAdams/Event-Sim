Project: Discrete Event Simulator
Programmer: Darrin McAdams
Class: CIS 3207-004
Instructor: Dr. Payton

FILE: main.c

DESCRIPTION: The main c file for the Event Simulator.

FUNCTIONS:

  main():
    Variables:
    clock_t real_time - Used to track the actual time elapsed
    int currentTime - tracks simulated time
    int cpu_track - tracks cpu utilization
    int disk1_track - tracks disk 1 utilization
    int disk2_track - tracks disk 1 utilization
    int job_wait_time - how long to wait to create a new job
    int job_count - how many jobs have been created
    char string[BUFF_SIZE]; - holds formated text for output
    component *cpu - holds date for simulated cpu
    component *disk1 - holds date for simulated disk
    component *disk2 - holds date for simulated disk
    config *myConfig - holds information found in config.txt

    Process:
    1.) Initialize all of the variables
    2.) Output the contents of the config file
    3.) Output simulation start message

    sim_cpu()
    sim_disk()

  randNumber(min, max):
    Input:
    int min
    int max

    Output:
    int temp

    Description: returns a number between min and max

  output()

    Input:
    char *string

    Description: Takes a string and outputs it to the console and
      writes it to a log text file.

  output_config()

    Input:
      config *myConfig

    Description: Takes myConfig and outputs the values it holds to the console
      and writes it to a log text file.


FILE: ./headers/component.h

Description: A header file that handles the component struct

Functions:

  typedef struct component{}

    Input: N/A

    Description:
    Defines a struct that holds the following data:
      struct queue *QUEUE; - holds incoming jobs
      int WAIT_TIME; - how long the component needs to wait for a job to finish
      int STATUS; - is the component running or idle
      long long SIZE; - used for tracking the average size of the queue
      long MOST_JOBS; - used to track the most jobs are in the queue at one time
      int PROCESSED; - how many jobs have been processed by the component
      int COMPLETED; - how many jobs have been finished after processing

  get_component()
    Input: N/A

    Output: component *temp

    Description:
      Allocates the memory for the component struct, initializes the variable
        and sets them to 0 (except for the queue, which is left empty). Then it
        returns the struct.

  push()
    Input:
      component *temp
      int key

    Description: Adds a value to a component's queue using queue.h functions.  

  pop()
    Input:
      component *temp

    Output:
      int key

    Description: Removes the next node in a component's queue and returns it's
      value. The node's memory is also freed.
