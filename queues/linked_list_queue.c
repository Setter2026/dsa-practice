#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

typedef struct{
    int value;
    struct Node *next;
}Node;

typedef struct{
    Node *front;
    Node *rear; //* bcs need to stay
}Queue;

int equeue(Queue *q, int num){
    Node *n = malloc(sizeof(Node)); //this is an address
    if (n == NULL){
        return 0;
    }

    n->value = num;
    n->next = NULL;

    if(q->front == NULL){
        q->front = n; //without anything I guess it's pointer alr
        q->rear = n;
        return 1;
    }

    q->rear->next = &n;
    q->rear = q->rear->next;
    return 1;
}

int dequeue(Queue *q, int *removed){
    
    if (q->front == NULL){
       return 0;
    }

    *removed = q->front->value;

    if (q->front->next == NULL){
        free(q->front);
        q->front = NULL;
        q->rear = NULL;
        return 1;
     }

    Node *temp = q->front->next;
    free(q->front);
    q->front = temp;

    return 1;
}

int peek(Queue *q, int *value){
    if (q->front == NULL){
        return 0;
    }
    *value = q->front->value;
    return 1; 
}

int is_empty(Queue *q){
    return q->front == NULL;
}



