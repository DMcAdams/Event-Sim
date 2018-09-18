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

    Description:
      This function is where most of the core variables are initialized. Once the
        intital setup is done, a while loop runs with a counter that goes from
        INIT_TIME to FIN_TIME. Each loop represents a single unit of time. During
        each loop sim_cpu and sim_disk are called to simulate their respective
        components. The output is recorded in the console and in a text file.ARRIVE_MIN
        and ARRIVE_MAX are used to determine when a new job is created.
        Counters record when the components are running to track utilization.
        At the end of the simulation all of the recorded statistics are also
        calculated and displayed.

    sim_cpu()

      Input:
        config *myConfig
        component *cpu
        component *disk1
        component *disk2
        int currentTime

      Description:
      This function simulates the CPU. When the cpu receives a job a random wait time
        between CPU_MIN and CPU_MAX is calculated by randNumber(), the CPU's
        status is set to RUNNING, and a job started message is sent to output().
        Until the wait time is reached, the function will do nothing.
        Once reached, QUIT_PROB will determine whether the job is finished, or if
        disk I/O is needed. If finished, a message is displayed and the job is removed
        from the queue. If the job needs I/O, the job is moved to the least used disk
        queue, or is randomly selected if they are even. The CPU is then set to IDLE
        while it waits for it's next job.

    sim_disk()
      Input:
        component *disk
        component *cpu
        int currentTime
        int DISK_MIN
        int DISK_MAX
        int diskNum

      Description:
      This function simulates a disk. When the disk receives a job a random wait time
        between DISK_MIN and DISK_MAX is calculated by randNumber(), the DISK's
        status is set to RUNNING, and a job recieved message is sent to output().
        Until the wait time is reached, the function will do nothing.
        Once reached, the job will be sent back into the job queue and the DISK is then
        set to IDLE while it waits for it's next job.


  randNumber(min, max)

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

FILE: ./headers/queue.h

DESCRIPTION: An implementation of a linked-list queue

FUNCTIONS:

  typedef struct node{}

    Description:
    Defines a struct with the following variables:
      int key - the value being stored (job number in this program)
      node *next - points to the next node in the queue

  typedef struct queue{}

    Decription:
    Defines a struct with the following variables:
        node *front - the node at the front of the queue
        node *back - the last node in the queue
        int count - holds the size of the queue

    createQueue()

      Output:
        queue *temp

      Description:
        Allocates memory for a queue struct and sets front and back to NULL, and
          count to 0, before returning the empty queue.


    newnode()

      Input:
        int key - value being stored in the node

      Output:
        node *temp

      Description:
        Allocates memory for the node, and sets it's key to the one in the input
          before returning it

    enQueue()

      Input:
        queue *q - the queue to add a new node too
        int key - the value for the new node

      Description:
        Sends the key to newnode to create a node struct. The node is added to the
          back of the queue, or is set to both the front and back if the queue is
          empty. It then adds 1 to the queue's count.

    deQueue()

      Input:
        queue *q

      Output:
        node *temp

      Description:
        Removes the node at the front of the queue, and sets the front to the next
          node in the queue and subtracts one from the count. If there is no other node, set both the front and back to NULL. Returns NULL if queue is empty.

    printQueue()

      Description: Prints out the contents of the queue to the console. Mostly
        used for testing.

    Empty()

      Output:
        int num

      Description:
        If the queue is empty, this returns 1 (TRUE). Otherwise, it returns 0 (FALSE).

FILE: ./headers/config.h

DESCRIPTION: A header file that handles the config struct.

FUNCTIONS:

  typedef struct config{}

    Description:
    Defines a struct that holds the following variables:
      int INIT_TIME - start time for simulation
      int FIN_TIME - end time for simulation
      int ARRIVE_MIN - minimum wait time for a new job
      int ARRIVE_MAX - maximum wait time for a new job
      int QUIT_PROB - the chance of a job being finished after exiting the CPU
      int CPU_MIN - minimum wait time for a job to finish at the CPU
      int CPU_MAX - maximum wait time for a job to finish at the CPU
      int DISK1_MIN - minimum wait time for a job to finish at DISK 1
      int DISK1_MAX - maximum wait time for a job to finish at DISK 1
      int DISK2_MIN - minimum wait time for a job to finish at DISK 2
      int DISK2_MAX - maximum wait time for a job to finish at DISK 2
      int SEED - used to input a custom seed into srand

  create_config()

    Output:
    config *myConfig

    Description: Allocates memory for myConfig, initializes all variables to 0,
      and returns it.

  get_config()

      Input:
        config.txt

      Output:
        config myConfig

      Description:
        Gets myConfig from my create_config(), then sets it's variables equal to
          the ones found in config.txt before returning it.
