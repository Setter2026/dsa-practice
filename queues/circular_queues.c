#include <stdio.h>
#include <assert.h>

#define CAPACITY 5

typedef struct {
    int arr[CAPACITY];
    int count;
    int front;
    int rear;
} Queue;

int equeue(Queue *q, int num){
    if (q->count == CAPACITY){
        return 0;
    }
    if (q->front == -1){
        q->front = 0;
        q->rear = 0;
    }
    else{
        q->rear = (q->rear + 1) % CAPACITY;
    }
     
    q->arr[q->rear] = num;
    ++q->count;
    return 1;
}

int dequeue(Queue *q, int *removed){
    if (q->front == -1){
        return 0;
    }
    *removed = q->arr[q->front];
    --q->count;

    if (q->front == q->rear){
        q->front = -1;
        q->rear = -1;
        return 1;
    }

    q->front = (q->front + 1) % CAPACITY;
    
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
    return (q->count == 0);
}

int is_full(Queue *q){
    return (q->count == CAPACITY);
}

int main(){
    Queue q;
    q.count = 0;
    q.front = -1;
    q.rear = -1;

    equeue(&q, 1);
    equeue(&q, 2);
    equeue(&q, 3);
    equeue(&q, 4);
    equeue(&q, 5);

    int remove1 = -999;
    int remove2 = -999;
    int remove3 = -999;
    int remove4 = -999;
    int remove5 = -999;

    assert(dequeue(&q, &remove1));
    assert(dequeue(&q, &remove2));
    dequeue(&q, &remove3);
    dequeue(&q, &remove4);
    dequeue(&q, &remove5);

    assert(dequeue(&q, &remove1));

    int value = -999;
    if (peek(&q, &value)){
        printf("%d\n", value);
    }
}