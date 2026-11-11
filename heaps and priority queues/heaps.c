#include <stdio.h>

#define CAPACITY 100

typedef struct {
    int arr[CAPACITY];
    int size;
} MaxHeap;

void sift_up(MaxHeap *h, int i){
    int parent = (i - 1) / 2;

    while (h->arr[parent] < h->arr[i] && i > 0){
        int temp = h->arr[i];
        h->arr[i] = h->arr[parent];
        h->arr[parent] = temp;
        
        i = parent;
        parent = (i - 1)/ 2;
    }
}

void sift_down(MaxHeap *h, int i){
    int left = i * 2 + 1;
    int right = i * 2 + 2;
    
    while(left < h->size){
        int bigger_child = left; //automatically left if right isn't bigger or doesn't exist
        if (right < h->size && h->arr[right] > h->arr[left]){
            bigger_child = right;
        }

        if (h->arr[bigger_child] < h->arr[i]){
            break;
        }

        int temp = h->arr[bigger_child];
        h->arr[bigger_child] = h->arr[i];
        h->arr[i] = temp;

        i = bigger_child;
        left = i * 2 + 1;
        right = i * 2 + 2;
    }
}

int insert(MaxHeap *h, int value){
    if (h->size == CAPACITY){
        return 0;
    }

    h->arr[h->size] = value;
    sift_up(h, h->size);
    ++h->size;
    return 1;
}

int extract_max(MaxHeap *h, int *removed){
    if (h->size <= 0){
        return 0;
    }

    *removed = h->arr[0]; // 0 is first a.k.a. root
    h->arr[0] = h->arr[h->size - 1];
    --h->size; // since we "removed" root, we need to decrease size

    sift_down(h, 0); // 0 since we need sift down starting from root  
    return 1;
    
}

int peek(MaxHeap *h, int *max){
    if (h->size <= 0){
        return 0;
    }

    *max = h->arr[0];
    return 1;
}

void build_heap(MaxHeap *h){
    for(int i = 0; i < (h->size - 2) / 2; ++i){
        sift_down(h, i);
    }
}

void print_heap(MaxHeap *h){
    for(int i = 0; i < h->size; ++i){
        printf("%d ", h->arr[i]);
    }
}

int main(){
    MaxHeap h;

    //Test 1
    int num[] = {1, 2, 4, 3, 5};
    for(int i = 0; i < 5; ++i){
        
    }
}



