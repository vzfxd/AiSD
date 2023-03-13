#include <stdlib.h>
#include <stdio.h>
#include <time.h>

typedef struct Element{
    struct Element* nextElement;
    int data;
} Element;

typedef struct LinkedList{
    struct Element* head;
    int size;
} LinkedList;

int find(LinkedList* linkedList, int index){
    if(index<0 || index>=linkedList->size) return;
    struct Element* curr = linkedList->head;
    while(index--) {curr = curr->nextElement;}
    return curr->data;
}

void insert(LinkedList* linkedList, int data, int index){
    if(index<0 || index>linkedList->size) return;
    struct Element* element = malloc(sizeof(Element));
    element->data = data;
    struct Element* curr = linkedList->head;
    if(index==0){
        element->nextElement = linkedList->head;
        linkedList->head = element;
        linkedList->size++;
        return;
    }
    while(--index){
        curr = curr->nextElement;
    }
    element->nextElement = curr->nextElement;
    curr->nextElement = element;
    linkedList->size++;
}

void delete(LinkedList* linkedList, int index){
    if(index<0 || index>=linkedList->size) return;
    if(index==0){
        struct Element* temp = linkedList->head;
        linkedList->head = linkedList->head->nextElement;
        free(temp);
        linkedList->size--;
        return;
    }
    struct Element* curr = linkedList->head;
    while(--index){
        curr = curr->nextElement;
    }
    struct Element* temp = curr->nextElement;
    curr->nextElement = curr->nextElement->nextElement;
    linkedList->size--;
    free(temp);
}

int isEmpty(LinkedList* linkedList){
    if(linkedList->head) return 0;
    return 1;
}

void merge(LinkedList* list1, LinkedList* list2){
    struct Element* tail = list1->head;
    while(tail->nextElement) tail = tail->nextElement;
    tail->nextElement = list2->head;
    list1->size += list2->size;
}

double avgRand(LinkedList* list){
    clock_t start, end;
    int randomIndices[10000];
    for(int i=0; i<10000; i++){
        randomIndices[i]=rand() % 10000;
    }
    start = clock();
    for(int i=0; i<10000; i++){
        find(list,randomIndices[i]);
    }
    end = clock();
    return (((double)end-start)/CLOCKS_PER_SEC)/10000;
}

double avgIndex(LinkedList* list, int index){
    clock_t start, end;
    start = clock();
    for(int i=0; i<10000; i++){
        find(list,index);
    }
    end = clock();
    return (((double)end-start)/CLOCKS_PER_SEC)/10000;
}

int main(){
    struct LinkedList list = {NULL,0};
    struct LinkedList merge1 = {NULL,0};
    struct LinkedList merge2 = {NULL,0};

    printf("#### LISTA JEDNOKIERUNKOWA ####\n");
    for(int i=0; i<10000; i++){
        insert(&list,rand()%10000,i);  
    }
    
    printf("ŚREDNI CZAS DLA INDEKSU 1000:%f\n",avgIndex(&list,1000));
    printf("ŚREDNI CZAS DLA INDEKSU 5000:%f\n",avgIndex(&list,5000));
    printf("ŚREDNI CZAS DLA INDEKSU 9000:%f\n",avgIndex(&list,9000));
    printf("ŚREDNI CZAS DLA LOSOWEGO INDEKSU:%f\n\n\n",avgRand(&list));

    printf("TEST MERGE'A\n");
    for(int i=0; i<5; i++){
        insert(&merge1,rand()%100,i);
        insert(&merge2,rand()%100,i);
    }
    printf("LISTA 1:\n");
    for(int i=0; i<merge1.size; i++){
        printf("%d,",find(&merge1,i));
    }
    printf("\n");
    printf("LISTA 2:\n");
    for(int i=0; i<merge2.size; i++){
        printf("%d,",find(&merge2,i));
    }
    printf("\n");
    printf("MERGE:\n");
    merge(&merge1,&merge2);
    for(int i=0; i<merge1.size; i++){
        printf("%d,",find(&merge1,i));
    }
    

    while(!isEmpty(&list)){
        delete(&list,0);
    }
    while(!isEmpty(&merge1)){
        delete(&merge1,0);
    }   
    printf("\n\n\n");

    return 0;
}