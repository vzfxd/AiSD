#include<stdio.h>
#include<stdlib.h>

typedef struct StackElement{
    struct StackElement* prevElement;
    int data;
} StackElement;

typedef struct Stack{
    struct StackElement* top;
} Stack;

int top(Stack* stack){
    if(stack->top) return stack->top->data;
}

int isEmpty(Stack* stack){
    if(stack->top) return 0;
    return 1;
}

void pop(Stack* stack){
    if(stack->top){
        struct StackElement* temp = stack->top;
        stack->top = stack->top->prevElement;
        free(temp);
    }
}

void push(Stack* stack, int data){
    struct StackElement* stackElement = malloc(sizeof(StackElement));
    stackElement->data = data;
    stackElement->prevElement = stack->top;
    stack->top = stackElement;  
}

int main(){
    struct Stack stack = {NULL};

    printf("####  STOS(LIFO) ####\n\n\n");

    printf("ZAPEŁNIANIE STOSU:\n");
    for(int i=1; i<=100; i++){
        push(&stack, i);  
        printf("%d,",top(&stack)); 
    }

    printf("\n\n\n");
    
    printf("POBIERANIE ZE STOSU:\n");
    while(!isEmpty(&stack)){
        printf("%d,",top(&stack));
        pop(&stack);
    }

    printf("\n\n\n");


    return 0;
}