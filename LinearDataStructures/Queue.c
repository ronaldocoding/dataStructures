#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int isQueueEmpty(Node **head);
Node * createNode(int newValue);
void enqueueNewValue(Node **head, Node **tail, int newValue);
void enqueueNewHead(Node **head, Node **tail, Node *newHead);
void dequeue(Node **head);
Node * dequeueReturnOldHead(Node **head);
void printQueue(Node **head, Node**tail);
void imprimirFilaReal2(Node *head, Node *tail);
int dequeueReturnOldHeadValue(Node **head);

int main() {
    // TODO
}

int isQueueEmpty(Node **head) {
    return *head == NULL;
}

Node * createNode(int newValue) {
    Node * newNode = (Node *) malloc(sizeof(Node));
    newNode->value = newValue;
    newNode->next = NULL;
    return newNode;
}

void enqueueNewValue(Node **head, Node **tail, int newValue) {
    Node * newNode = createNode(newValue);
    if(isQueueEmpty(head)) {
        *tail = *head = newNode;
    } else {
        (*tail)->next = newNode;
        *tail = newNode;
    }
}

void enqueueNewHead(Node **head, Node **tail, Node *newHead) {
    if(isQueueEmpty(head)) {
        *tail = *head = newHead;
    } else {
        (*tail)->next = newHead;
        *tail = newHead;
    }
}

void dequeue(Node **head) {
    if(!isQueueEmpty(head)) {
        Node * oldHead = *head;
        *head = (*head)->next;
        free(oldHead); 
    }
}

Node * dequeueReturnOldHead(Node **head) {
    Node *oldHead = *head;
    if(!isQueueEmpty(head)) {
        *head = (*head)->next;
        oldHead->next = NULL;
    }
    return oldHead;
}

int dequeueReturnOldHeadValue(Node **head) {
    Node *oldHead = *head;
    if(!isQueueEmpty(head)) {
        *head = (*head)->next;
        oldHead->next = NULL;
    }
    return oldHead->value;
}

void printQueue(Node **head, Node **tail) {
    Node *temporaryHead = NULL, *temporaryTail = NULL;
    while((*head) != NULL) {
        Node *oldHead = dequeueReturnOldHead(head);
        enqueueNewHead(&temporaryHead, &temporaryTail, oldHead);
        printf("%d ", oldHead->value);
    }
    printf("\n");
    *head = temporaryHead;
    *tail = temporaryTail;
}
