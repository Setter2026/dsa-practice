#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define CAPACITY 5
typedef enum {
    INSERT,
    DELETE
} ActionType;

typedef struct {
    int position;
    char letter;
    ActionType type;
} Action;

typedef struct {
    Action arr[CAPACITY];
    int top;
} ActionStack;

int push_action(ActionStack *s, Action action){
    if (s->top >= CAPACITY){
        return 0;
    }
    ++s->top;
    s->arr[s->top] = action;
    return 1;
}

int pop_action(ActionStack *s, Action *removed){
    if(s->top == -1){
        return 0;
    }
    *removed = s->arr[s->top];
    --s->top;
    return 1;
}

int main(void)
{
    ActionStack s;
    s.top = -1;

    Action action1;
    action1.letter = 'C';
    action1.position = 0;
    action1.type = INSERT;

    int success = push_action(&s, action1);
    Action removed;
    success = pop_action(&s, &removed);


    printf("Success: %d\n", success);
    printf("Position: %d\n", removed.position);
    printf("Letter: %c\n", removed.letter);
    printf("Type: %d\n", removed.type);
    printf("Top: %d\n", s.top);

    return 0;
}