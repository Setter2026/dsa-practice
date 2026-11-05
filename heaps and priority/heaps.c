#include <stdio.h>

#define CAPACITY 100

typedef struct {
    int arr[CAPACITY];
    int size;
} MaxHeap;

int insert(MaxHeap *h, int value){
    if (h->size >= CAPACITY){
        return 0;
    }

    ++h->size;
    int i = h->size - 1;
    h->arr[i] = value;
    int parent = (i - 1)/ 2;

    while(i > 0 && h->arr[i] > h->arr[parent]){
        printf("%d > %d\n", h->arr[i], h->arr[parent]);
        int temp = h->arr[i];
        h->arr[i] = h->arr[parent];
        h->arr[parent] = temp;

        i = parent;
        parent = (i - 1)/2;
    }

    return 1;
}

int main(){
    MaxHeap h;
    int numbers[] = {70, 90, 40, 50, 60};
    
    for(int i = 0; i < 5; ++i){
        h.arr[i] = numbers[i];
        ++(h.size);
        printf("%d-%d ", h.arr[i], i);
    }

    printf("\n");

    insert(&h, 100);

    printf("\n");
    for(int i = 0; i < 6; ++i){
        printf("%d ", h.arr[i]);
    }

}

