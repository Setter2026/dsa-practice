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
    if (s->top >= CAPACITY - 1 ){
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

void remove_character(char document[], int position, int *length){
    for(int i = position; i < *length; ++i){

        document[i] = document[i + 1];
    }
    --*length;
}

void add_character(char c, char document[], int position, int *length){
    for(int i = *length; i > position; --i){
        document[i] = document[i - 1];
    }
    document[position] = c;
    ++*length;
}

void undo(ActionStack *s, char document[], int *length){
    Action action;

    if (pop_action(s, &action)){
        if (action.type == INSERT){
            remove_character(document, action.position, length);
        }
        else if (action.type == DELETE){
            add_character(action.letter, document, action.position, length);
        }
    }
    
}

int main(void)
{
    ActionStack s;
    s.top = -1;

    char document[20] = {};
    int length = 0;

    char command[20];

    while (strcmp(command, "quit") != 0){
        printf("> ");
        scanf("%19s", command);

        if (strcmp(command, "undo") == 0) {
            undo(&s, document, &length);
        }
        
        else if (strcmp(command, "show") == 0) {
            printf("%s\n", document);
        }

        else if (strcmp(command, "insert") == 0) {
            int position;
            char letter;
        
            scanf("%d %c", &position, &letter);
        
            Action action = {position, letter, INSERT};
        
            if (push_action(&s, action)) {
                add_character(letter, document, position, &length);
            }
            else {
                printf("Undo history is full!\n");
            }
        }

        else if (strcmp(command, "delete") == 0) {
            int position;
            scanf("%d", &position);

            char letter = document[position];

            Action action = {position, letter, DELETE};

            if (push_action(&s, action)) {
                remove_character(document, position, &length);
            }
            else {
                printf("Undo history is full!\n");
            }

        }
    }

    return 0;
}