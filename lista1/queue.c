#include <stdlib.h>
#include <stdio.h>
typedef struct QueueElement{
    struct QueueElement* nextElement;
    int data;
} QueueElement;

typedef struct Queue{
    struct QueueElement* head;
    struct QueueElement* tail;
} Queue;

void enqueue(Queue* queue, int data){
    struct QueueElement* queueElement = malloc(sizeof(QueueElement));
    queueElement->data = data;
    if(!queue->tail){queue->tail = queueElement; queue->head=queueElement; return;} 
    queue->tail->nextElement = queueElement;
    queue->tail = queueElement;    
}

void dequeue(Queue* queue){
    if(queue->head){
        struct QueueElement* temp = queue->head;
        queue->head = queue->head->nextElement;
        free(temp);
    }
}

int tail(Queue* queue){
    if(queue->tail) return queue->tail->data;
}

int head(Queue* queue){
    if(queue->head) return queue->head->data;
}

int isEmpty(Queue* queue){
    if(queue->head) return 0;
    return 1;
}

int main(){
    struct Queue queue = {NULL,NULL};
    printf("####  KOLEJKA(FIFO) ####\n\n\n");
    printf("ZAPEŁNIANIE KOLEJKI:\n");
    for(int i=1; i<=100; i++){
        enqueue(&queue, i);  
        printf("%d,",tail(&queue)); 
    }

    printf("\n\n\n");
    
    printf("POBIERANIE Z KOLEJKI\n");
    while(!isEmpty(&queue)){
        printf("%d,",head(&queue));
        dequeue(&queue);
    }

    printf("\n\n\n");
    return 0;
}