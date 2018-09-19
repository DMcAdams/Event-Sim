
/*==============================================================================================
 |       Author:  Darrin McAdams
 |         Date:  September 4th, 2018
 |  Description:  This is an implementation of a standard FIFO queue using linked lists for C.
 *==============================================================================================*/

#ifndef QUEUE_H
#define QUEUE_H

#include<stdlib.h>
#include<stdio.h>

#define TRUE 1
#define FALSE 0
//each node in the queue has a key and a pointer to the next node in the queue
typedef struct node{
    //holds a data value
    int key;
    //holds time spent on processing
    int time;
    //next node in queue
    struct node *next;

} node;
//queue has a pointer to the first and last node
typedef struct queue{
    node *front, *back;
    int count;
} queue;
//creates an empty queue and returns it
queue* createQueue() {
    queue *q = (queue*)malloc(sizeof(queue));
    q->front = NULL;
    q->count = 0;
    return q;
};
//creates a new node from a key value and returns it
node* newnode(int key){
    node *temp = (node*)malloc(sizeof(node));
    temp->key = key;
    temp->time = 0;
    temp->next = NULL;
    return temp;
}
//adds a new node to the back of the queue. takes input for the new nodes' key value
void enQueue (queue *q, int key){
    //create new node
    node *temp = newnode(key);

    //if queue is empty, set front and back to the new node
    if (q->front == NULL){
        q->front = temp;
        q->back = q->front;
    }
        //else add node to back of queue
    else {
        q->back->next = temp;
        q->back = temp;
    }
    //add one to node count
    q->count++;
}

//removes the node at the front of the queue and replaces it with the next value in line
//the removed node gets returned
node* deQueue (queue *q){

    //return null if queue is empty
    if (q->front == NULL)
        return NULL;
    //remove one to node cound
    q->count--;
    //store front as temp, replace front with next node in queue
    node *temp = q->front;
    q->front = q->front->next;

    //if front = null, then set back = null
    if (q->front == NULL)
        q->back = NULL;

    return temp;
}

//prints out contents of queue
void printQueue(queue *q){

    //temp node used to traverse queue and get value for each node
    node *temp = q->front;

    //used for formatting output
    printf(" <--");

    //loops through queue until a null value is reached
    while (temp != NULL){
        printf("%d ", temp->key);
        temp = temp->next;
    }

    //used for formatting output
    puts("<--");
}
//return TRUE if queue is empty, FALSE otherwise
int Empty(queue *q){
    if (q->front == NULL)
        return TRUE;
    else return FALSE;

}
#endif
