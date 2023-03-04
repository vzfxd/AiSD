#include<stdio.h>
#include<stdlib.h>

typedef struct StackElement{
    struct StackElement* prevElement;
    void* data;
} StackElement;

typedef struct Stack{
    struct StackElement* top;
} Stack;

void* top(Stack* stack){
    if(stack->top) return stack->top->data;
    return NULL;
}

int isEmpty(Stack* stack){
    if(stack->top) return 0;
    return 1;
}

int pop(Stack* stack){
    if(stack->top){
        struct StackElement* temp = stack->top;
        stack->top = stack->top->prevElement;
        free(temp);
        return 1;    
    }
    return 0;
}

void push(Stack* stack, void* data){
    struct StackElement* stackElement = malloc(sizeof(StackElement));
    stackElement->data = data;
    stackElement->prevElement = stack->top;
    stack->top = stackElement;  
}

int main(){
    struct Stack stack = {NULL};

    for(int i=1; i<=100; i++){
        push(&stack, i);  
        printf("%d,",top(&stack)); 
    }

    printf("\n\n\n");
    
    
    while(!isEmpty(&stack)){
        printf("%d,",top(&stack));
        pop(&stack);
    }

    printf("\n\n\n");

    push(&stack, "A");  
    printf("%s,",top(&stack));
    push(&stack, "B");  
    printf("%s,",top(&stack)); 
    push(&stack, "C");  
    printf("%s,",top(&stack));  

    printf("\n\n\n");
    
    while(!isEmpty(&stack)){
        printf("%s,",top(&stack));
        pop(&stack);
    }

    printf("\n\n\n");


    return 0;
}