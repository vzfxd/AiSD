#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
typedef struct Element{
    struct Element* nextElement;
    struct Element* prevElement;
    int data;
} Element;

typedef struct List{
    struct Element* head;
    struct Element* tail;
    int size;
} List;

int find(List* list, int index){
    if(index<0 || index>=list->size) return;
    struct Element* curr = NULL;
    if(index<floor(list->size/2)){
        curr = list->head;
        while(index--) {curr = curr->nextElement;}

    }else{
        curr = list->tail;
        int offset = list->size-index-1;
        while(offset--) {curr = curr->prevElement;}
    }
    return curr->data;
}

void add(List* list, int data){
    struct Element* element = malloc(sizeof(Element));
    element->data = data;
    if(list->size==0){
        element->nextElement = element;
        element->prevElement = element;
        list->head = element;
        list->tail = element;
    }else{
        element->nextElement = list->head;
        element->prevElement = list->tail;
        list->tail->nextElement = element;
        list->head->prevElement = element;

        list->tail = element;
    }
    list->size++;
}


void delete(List* list){
    if(list->tail){
        struct Element* temp = list->tail;
        if(list->size==1){
            list->head = NULL;
            list->tail = NULL;
            list->size--;
            free(temp);
            return;
        }
        list->tail = list->tail->prevElement;
        list->tail->nextElement = list->head;
        list->head->prevElement = list->tail;
        list->size--;
        free(temp);
    }
}

int isEmpty(List* list){
    if(list->head) return 0;
    return 1;
}

double avgRand(List* list){
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

double avgIndex(List* list, int index){
    clock_t start, end;
    start = clock();
    for(int i=0; i<10000; i++){
        find(list,index);
    }
    end = clock();
    return (((double)end-start)/CLOCKS_PER_SEC)/10000;
}

void merge(List* list1, List* list2){
    list1->tail->nextElement = list2->head;
    list2->head->prevElement = list1->tail;

    list1->tail = list2->tail;
    list1->tail->nextElement = list1->head;
    list1->head->prevElement = list1->tail;

    list1->size += list2->size;
}

int main(){
    struct List list = {NULL,NULL,0};
    struct List merge1 = {NULL,NULL,0};
    struct List merge2 = {NULL,NULL,0};
    printf("#### LISTA DWUKIERUNKOWA ####\n");
    for(int i=0; i<10000; i++){
        add(&list,rand()%10000);  
    }
    
    printf("ŚREDNI CZAS DLA INDEKSU 1000:%f\n",avgIndex(&list,1000));
    printf("ŚREDNI CZAS DLA INDEKSU 5000:%f\n",avgIndex(&list,5000));
    printf("ŚREDNI CZAS DLA INDEKSU 9000:%f\n",avgIndex(&list,9000));
    printf("ŚREDNI CZAS DLA LOSOWEGO INDEKSU:%f\n\n\n",avgRand(&list));

    printf("\n\n\n");

    printf("TEST MERGE'A\n");
    for(int i=0; i<5; i++){
        add(&merge1,rand()%100);
        add(&merge2,rand()%100);
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
        delete(&list);
    }
    while(!isEmpty(&merge1)){
        delete(&merge1);
    }
    
    printf("\n\n\n");

    return 0;
}
