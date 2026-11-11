#include <stdio.h>
#include <assert.h>
#include <string.h>

#define CAPACITY 5

typedef struct {
    char name[50];
    int priority;
} Task;

typedef struct{
    Task arr[CAPACITY];
    int size;
} TaskHeap;

void sift_up(TaskHeap *h, int i){
    int parent = (i - 1) / 2;

    while(i > 0 && h->arr[i].priority > h->arr[parent].priority){
        Task temp = h->arr[i];
        h->arr[i] = h->arr[parent];
        h->arr[parent] = temp;

        i = parent;
        parent = (i - 1) / 2;
    }
}

void sift_down(TaskHeap *h, int i){
    int left = i * 2 + 1;
    int right = i * 2 + 2;

    while (left < h->size){
        int bigger_child = left;
        if (right < h->size && h->arr[right].priority > h->arr[left].priority){
            bigger_child = right;
        }

        if (h->arr[bigger_child].priority <= h->arr[i].priority){
            break;
        }

        Task temp = h->arr[bigger_child];
        h->arr[bigger_child] = h->arr[i];
        h->arr[i] = temp;

        i = bigger_child;
        left = i * 2 + 1;
        right = i * 2 + 2;
    }
}

int insert_task(TaskHeap *h, Task task){
    if (h->size >= CAPACITY){
        return 0;
    }

    h->arr[h->size] = task;
    ++h->size;
    sift_up(h, h->size - 1);
    return 1;

}

int process_task(TaskHeap *h, Task *task_done){
    if (h->size <= 0){
        return 0;
    }

    *task_done = h->arr[0];
    h->arr[0] = h->arr[h->size - 1];
    --h->size; 
    sift_down(h, 0);
    
    return 1;
}

void print_heap(TaskHeap *h){
    for(int i = 0; i < h->size; ++i){
        printf("%s ", h->arr[i].name);
    }
    printf("\n");
}

int build_TaskHeap(TaskHeap *h){
    if (h->size <= 0){
        return 0;
    }

    for(int i = (h->size - 2) / 2; i >= 0; --i){
        sift_down(h, i);
    }
    return 1;
}

int is_valid_max_heap(TaskHeap *h) {
    // A heap with 0 or 1 elements is always valid
    if (h->size <= 1) {
        return 1;
    }

    // Start from the last non-leaf node and move up to the root
    for (int i = (h->size / 2) - 1; i >= 0; --i) {
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Check left child if it exists
        if (left < h->size && h->arr[i].priority < h->arr[left].priority) {
            return 0;
        }

        // Check right child if it exists
        if (right < h->size && h->arr[i].priority < h->arr[right].priority) {
            return 0;
        }
    }
    
    return 1;
}



int main(){
    TaskHeap h;
    h.size = 0;

    //Test 1 (Normal Case)
    Task A = {"Homework", 4};
    Task B = {"Project", 9};
    Task C = {"Laundry", 2};
    Task D = {"Exam", 15};
    Task E = {"Scrolling", 1};

    Task tasks[5] = {B, C, E, D, A};

    //inserted tasks
    for(int i = 0; i < 5; ++i){
        assert(insert_task(&h, tasks[i]));
        assert(is_valid_max_heap(&h));
    }

    //removed tasks and expect the priority number to go from highest to lowest
    int expected_priority[5] = {15, 9, 4, 2, 1}; //expected task priority number removed
    Task task_removed;
    for(int i = 0; i < 5; ++i){
        assert(process_task(&h, &task_removed));
        assert(expected_priority[i] == task_removed.priority);
        assert(is_valid_max_heap(&h));
    }

    //Test 2 (Empty Heap)
    assert(!process_task(&h, &task_removed));
    assert(is_valid_max_heap(&h));

    //Test 3 (One element)
    assert(insert_task(&h, A));
    assert(is_valid_max_heap(&h));
    assert(process_task(&h, &task_removed));
    assert(is_valid_max_heap(&h));
    assert(h.size == 0);

    //Test 4 (Full Heap)
    Task F = {"Invalid Task", 0};
    for(int i = 0; i < 5; ++i){
        assert(insert_task(&h, tasks[i]));
        assert(is_valid_max_heap(&h));
    }
    assert(!insert_task(&h, F));

    //clear heap
    for(int i = 0; i < 5; ++i){
        assert(process_task(&h, &task_removed));
        assert(is_valid_max_heap(&h));
    }

    //Test 5 Equal priorities
    for(int i = 0; i < 3; ++i){
        assert(insert_task(&h, A));
        assert(is_valid_max_heap(&h));
    }
    for(int i = 0; i < 3; ++i){
        assert(process_task(&h, &task_removed));
        assert(is_valid_max_heap(&h));
    }
    assert(h.size == 0);

    //Test 6 (Sorted tasks)
    Task sorted_tasks[] = {E, C, A, B, D};
    for(int i = 0; i < 5; ++i){
        assert(insert_task(&h, sorted_tasks[i]));
        assert(is_valid_max_heap(&h));
    }

    assert(process_task(&h, &task_removed));
    assert(is_valid_max_heap(&h));
    assert(task_removed.priority == D.priority); //D is the biggest
    //clear the rest of array
    for(int i = 0; i < 3; ++i){
        assert(process_task(&h, &task_removed));
        assert(is_valid_max_heap(&h));
    }

    //Test 7 (Sequential test)
    assert(insert_task(&h, A));
    assert(is_valid_max_heap(&h));
    assert(insert_task(&h, B));
    assert(is_valid_max_heap(&h));
    assert(process_task(&h, &task_removed));
    assert(is_valid_max_heap(&h));
    assert(insert_task(&h, C));
    assert(is_valid_max_heap(&h));
    assert(process_task(&h, &task_removed));
    assert(is_valid_max_heap(&h));   
}