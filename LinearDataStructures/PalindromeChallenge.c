#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    char letter;
    struct Node *next;
} Node;

Node * createNode(char newLetter) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->letter = newLetter;
    newNode->next = NULL;
    return newNode;
}

int isStructureEmpty(Node **structure) {
    if(*structure == NULL) return 1;
    return 0;
}

void insertStart(Node **list, char newLetter) {
    Node *newNode = createNode(newLetter);
    if(isStructureEmpty(list)) {
        *list = newNode;
    }
    else {
        newNode->next = *list;
        *list = newNode;
    }
}

void insertEnd(Node **list, char newLetter) {
    if(isStructureEmpty(list)) {
        insertStart(list, newLetter);
    } else {
        Node *currentNode, *newNode;
        currentNode = *list;
        newNode = createNode(newLetter);
        while(currentNode->next != NULL) currentNode = currentNode->next;
        currentNode->next = newNode;
    }
}

void enqueueNewHead(Node **head, Node **tail, Node *newHead) {
    if(isStructureEmpty(head)) {
        *tail = *head = newHead;
    } else {
        (*tail)->next = newHead;
        *tail = newHead;
    }
}

Node * dequeueReturnOldHead(Node **head) {
    Node *oldHead = *head;
    if(!isStructureEmpty(head)) {
        *head = (*head)->next;
        oldHead->next = NULL;
    }
    return oldHead;
}

void push(Node **stack, int newValue) {
    Node * newHead = createNode(newValue);
    if(isStructureEmpty(stack)) {
        *stack = newHead;
    }
    else {
        newHead->next = *stack;
        *stack = newHead;
    }
}

void pushNewHead(Node **stack, Node *newHead) {
    if(isStructureEmpty(stack)) {
        *stack = newHead;
    }
    else {
        newHead->next = *stack;
        *stack = newHead;
    }
}

Node * popReturnOldHead(Node **stack) {
    if(isStructureEmpty(stack)) {
        return NULL;
    }
    else {
        Node * oldHead = *stack;
        *stack = (*stack)->next;
        oldHead->next = NULL;
        return oldHead;
    }
}

int popReturnOldHeadValue(Node **stack) {
    if(isStructureEmpty(stack)) {
        return NULL;
    }
    else {
        Node * oldHead = *stack;
        *stack = (*stack)->next;
        return oldHead->letter;
    }
}

void printStack(Node **stack) {
    Node * temporaryStack = NULL;
    printf("----------STACK----------\n");
    while(*stack != NULL) {
        push(&temporaryStack, popReturnOldHeadValue(stack));
        printf("%c\n", temporaryStack->letter);
    }
    while(temporaryStack != NULL) {
        push(stack, popReturnOldHeadValue(&temporaryStack));
    }
    printf("-------------------------\n\n");
}

void printQueue(Node **head, Node **tail) {
    Node *temporaryHead = NULL, *temporaryTail = NULL;
    while((*head) != NULL) {
        Node *oldHead = dequeueReturnOldHead(head);
        enqueueNewHead(&temporaryHead, &temporaryTail, oldHead);
        printf("%c", oldHead->letter);
    }
    printf("\n");
    *head = temporaryHead;
    *tail = temporaryTail;
}

void printList(Node **list) {
    Node *currentNode = *list;
    while(currentNode != NULL) {
        printf("%c", currentNode->letter);
        currentNode = currentNode->next;
    }
    printf("\n");
}

int isPalindrome(Node **list) {
    Node *stackHead = NULL, *queueHead = NULL, *queueTail = NULL, *currentNode = *list;

    while(list != NULL) {
        pushNewHeadValue(&stackHead, currentNode->letter);
        enqueueNewHeadValue(&queueHead, &queueTail, currentNode->letter);
        currentNode = currentNode->next;
        //printf("ih\n");
    }

    printList(list);
    printStack(&stackHead);
    printQueue(&queueHead, &queueTail);

    while(stackHead != NULL && queueHead != NULL) {
        Node *stackOldHead = popReturnOldHead(&stackHead);
        char currentStackLetter = stackOldHead->letter;
        Node *queueOldHead = dequeueReturnOldHead(&queueHead);
        char currentQueueLetter = queueOldHead->letter;
        free(stackOldHead);
        free(queueOldHead);
        if(currentStackLetter != currentQueueLetter) return 0;
    }

    return 1;
}

int main() {
    Node *word1 = NULL;
    insertEnd(&word1, 'a');
    insertEnd(&word1, 'b');
    insertEnd(&word1, 'a');

    printList(&word1);

    Node *word2 = NULL;
    insertEnd(&word2, 'a');
    insertEnd(&word2, 'b');
    insertEnd(&word2, 'b');

    printList(&word1);

    if(isPalindrome(&word1)) printf("Word 1 is palindrome\n");
    else printf("Word 1 is not palindrome\n");

    if(isPalindrome(&word2)) printf("Word 2 is palindrome\n");
    else printf("Word 2 is not palindrome\n");

    return 0;
}
