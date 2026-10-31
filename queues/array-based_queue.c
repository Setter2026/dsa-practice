#include <stdio.h>

#define CAPACITY 5

typedef struct {
    int arr[CAPACITY];
    int front;
    int rear;
} Queue;

int equeue(Queue *q, int num){
    if (q->rear == CAPACITY - 1){
        return 0;
    }
    if (q->front == -1){
        ++q->front;
    }
    ++q->rear;
    q->arr[q->rear] = num;
    return 1;
}

int dequeue(Queue *q, int *removed){
    if (q->front == -1){
        return 0;
    }
    *removed = q->arr[q->front];
    if (q->front == q->rear){
        q->front = -1;
        q->rear = -1;
        return 1;
    }

    ++q->front;
    return 1;
}

int peek(Queue *q, int *value){
    if (q->front == -1){
        return 0;
    }
    *value = q->arr[q->front];
    return 1;
}

int is_empty(Queue *q){
    if (q->front == -1){
        return 0;
    }
    return 1;
}

int is_full(Queue *q){
    if (q->rear == CAPACITY - 1){
        return 1;
    }
    return 0;
}
