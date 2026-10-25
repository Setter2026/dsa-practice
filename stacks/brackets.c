#include <stdio.h>
#include <string.h>
#include <stdlib.h> // Needed for memory allocation

typedef struct{
    char arr[21];
    int top;
}Stack;

int pop(Stack *s, int *removed){
    if (s->top == -1){
        return 0;
    }
    *removed = s->arr[s->top];
    --s->top;
    return 1;
}

int push(Stack *s, int value){
    if (s->top > 4){
        return 0;
    }
    ++s->top;
    s->arr[s->top] = value;
    return 1;
} 

int is_balanced(const char expression[]){
    Stack s;
    s.top = -1;
    int i = 0;

    while(expression[i] != '\0'){
        if (expression[i] == '(' || expression[i] == '[' || expression[i] =='{'){
            if (!push(&s, expression[i])) {
                return 0;
            }
        }
        if (expression[i] == ')' || expression[i] ==']' || expression[i] =='}' ){
            if (s.top == -1){
                return 0;
            }
            int removed = -999;
            if (!pop(&s, &removed)) {
                return 0;
            }
            if (!((removed == '(' && expression[i] == ')') || (removed == '[' && expression[i] == ']') || (removed == '{' && expression[i] == '}'))){
                return 0;
            }
        }
        ++i;
    }

    return s.top == -1;
}

int main(){
    char expression1[] = "([()])";
    int result1 = is_balanced(expression1);

    if (result1 == 1){
        printf("\nIt succeeded!");
    }

    char expression2[] = "([)]";
    int result2 = is_balanced(expression2);

    if (result2 == 1){
        printf("It succeeded!");
    }
    char expression3[] = "(()";
    int result3 = is_balanced(expression3);

    if (result3 == 1){
        printf("It succeeded!");
    }
    char expression4[] = "())";
    int result4 = is_balanced(expression4);

    if (result4 == 1){
        printf("It succeeded!");
    }
}