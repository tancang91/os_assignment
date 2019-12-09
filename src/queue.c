#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define MAX_QUEUE_SIZE 10

void queue_up(struct queue_t * q, int i);
void queue_down(struct queue_t * q, int i);
void swap(struct pcb_t **p1, struct pcb_t **p2);

int empty(struct queue_t * q) {
	return (q->size == 0);
}

void enqueue(struct queue_t * q, struct pcb_t * proc) {
    if (q->size == MAX_QUEUE_SIZE) {
        printf("Queue is full!");
        return;
    }
    if (proc == NULL) {
        printf("Null process pointer!");
        return;
    } 
    q->proc[q->size] = proc;
    queue_up(q, q->size);
    ++q->size;
}

struct pcb_t * dequeue(struct queue_t * q) {
    if (q == NULL || empty(q)) {
        return NULL;
    }
    struct pcb_t * result = q->proc[0];
    swap(&q->proc[0], &q->proc[--q->size]);
    queue_down(q, 0);
    return result;
}


void queue_up(struct queue_t * q, int i)
{
    int parent = (i-1)/2;
    while (parent >= 0 && q->proc[parent]->priority < q->proc[i]->priority) {
        swap(&q->proc[i], &q->proc[parent]);
        parent = (parent-1)/2;
    }        
}

void queue_down(struct queue_t * q, int i)
{
    int left, right, largest;
    left = 2*i + 1;
    right = 2*i + 2;
    largest = i;

    if (left < q->size && q->proc[left]->priority > q->proc[largest]->priority) { 
        largest = left; 
    }
    if (right < q->size && q->proc[right]->priority > q->proc[largest]->priority) { 
        largest = right; 
    }

    if (largest != i) {
        swap(&q->proc[i], &q->proc[largest]);
        queue_down(q, largest);
    }
}

void swap(struct pcb_t **p1, struct pcb_t **p2)
{
    struct pcb_t *temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}
