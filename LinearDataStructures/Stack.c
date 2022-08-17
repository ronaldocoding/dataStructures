#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

int isStackEmpty(Node **stack);
Node * createNode(int newValue);
void push(Node **stack, int newValue);
Node * pushReturnNewHead(Node **stack, int newValue);
int pushReturnNewHeadValue(Node **stack, int newValue);
void pop(Node **stack);
Node * popReturnOldHead(Node **stack);
int popReturnOldHeadValue(Node **stack);
void printStack(Node **stack);

int main() {
    // TODO
    return 0;
}

int isStackEmpty(Node **stack) {
    return *stack == NULL;
}

Node * createNode(int newValue) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = newValue;
    newNode->next = NULL;
    return newNode;
}

void push(Node **stack, int newValue) {
    Node * newHead = createNode(newValue);
    if(isStackEmpty(stack)) {
        *stack = newHead;
    }
    else {
        newHead->next = *stack;
        *stack = newHead;
    }
}

Node * pushReturnNewHead(Node **stack, int newValue) {
    Node * newHead = createNode(newValue);
    if(isStackEmpty(stack)) {
        *stack = newHead;
    }
    else {
        newHead->next = *stack;
        *stack = newHead;
    }
    return newHead;
}

int pushReturnNewHeadValue(Node **stack, int newValue) {
    Node * newHead = createNode(newValue);
    if(isStackEmpty(stack)) {
        *stack = newHead;
    }
    else {
        newHead->next = *stack;
        *stack = newHead;
    }
    return newHead->value;
}

void pop(Node **stack) {
    if(!isStackEmpty(stack)) {
        Node * oldHead = *stack;
        *stack = (*stack)->next;
        free(oldHead);
    }
}

Node * popReturnOldHead(Node **stack) {
    if(isStackEmpty(stack)) {
        return NULL;
    }
    else {
        Node * oldHead = *stack;
        *stack = (*stack)->next;
        return oldHead;
    }
}

int popReturnOldHeadValue(Node **stack) {
    if(isStackEmpty(stack)) {
        return NULL;
    }
    else {
        Node * oldHead = *stack;
        *stack = (*stack)->next;
        return oldHead->value;
    }
}

void printStack(Node **stack) {
    Node * temporaryStack = NULL;
    printf("----------STACK----------\n");
    while(*stack != NULL) {
        push(&temporaryStack, popReturnOldHeadValue(stack));
        printf("%d\n", temporaryStack->value);
    }
    while(temporaryStack != NULL) {
        push(stack, popReturnOldHeadValue(&temporaryStack));
    }
    printf("-------------------------\n\n");
}