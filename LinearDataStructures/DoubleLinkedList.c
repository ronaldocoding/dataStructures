#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *previous;
    struct Node *next;
} Node;

Node* createNode(int newValue);
int isListEmpty(Node **list);
void insertStart(Node **list, int newValue);
void insertMiddle(Node **list, int newValue, int index);
void insertEnd(Node **list, int newValue);
void removeStart(Node **list);
void removeMiddle(Node **list, int index);
void removeEnd(Node **list);
int removeByValue(Node **list, int searchValue);
int getNodeValueByIndex(Node **list, int index);
int getNodeIndexByValue(Node **list, int searchValue);
int getListSize(Node **list);
void printList(Node **list);
void printListRecursively(Node **list);
void printListBackwards(Node **list);
Node* josephus(Node **list, int index); // Not done yet

int main() {
    // TODO
    return 0;
}

Node* createNode(int  newValue) {
    Node *newNode = (Node*) malloc(sizeof(Node));
    newNode->value = newValue;
    newNode->previous = NULL;
    newNode->next = NULL;
    return newNode;
}

int isListEmpty(Node **list) {
    return *list == NULL;
}

void insertStart(Node **list, int newValue) {
    Node *newNode = createNode(newValue);
    if(isListEmpty(list)) {
        *list = newNode;
    }
    else {
        newNode->next = *list;
        (*list)->previous = newNode;
        *list = newNode;
    }
}

void insertMiddle(Node **list, int newValue, int index) {
    if(isListEmpty(list) || index <= 0) {
        insertStart(list, newValue);
    }
    else {
        Node *newNode = createNode(newValue);
        Node *currentNode, *previousNode;
        currentNode = *list;
        int aux = 0;
        while(aux != index && currentNode != NULL) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            aux++;
        }
        previousNode->next = newNode;
        newNode->previous = previousNode;
        if(currentNode != NULL) currentNode->previous = newNode;
        newNode->next = currentNode;
    }
}

void insertEnd(Node **list, int newValue) {
    if(isListEmpty(list)) {
        insertStart(list, newValue);
    }
    else {
        Node *newNode = createNode(newValue);
        Node *currentNode = *list;
        while(currentNode->next != NULL) currentNode = currentNode->next;
        currentNode->next = newNode;
        newNode->previous = currentNode;
    }
}

void removeStart(Node **list) {
    if(!isListEmpty(list)) {
        Node *oldFirstNode = *list;
        if((*list)->next != NULL) oldFirstNode->next->previous = NULL;
        *list = oldFirstNode->next;
        oldFirstNode->next = NULL;
        free(oldFirstNode);
    }
}

void removeMiddle(Node **list, int index) {
    if(isListEmpty(list) || index <= 0) {
        removeStart(list);
    }
    else {
        Node *previousNode, *currentNode;
        currentNode = *list;
        int aux = 0;
        while(aux != index && currentNode != NULL) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            aux++;
        }
        if(currentNode != NULL) {
            previousNode->next = currentNode->next;
            currentNode->next->previous = previousNode;
            currentNode->previous = NULL;
            currentNode->next = NULL;
            free(currentNode);
        }
        else {
            removeEnd(list);
        }
    }
}

void removeEnd(Node **list) {
    if(!isListEmpty(list)) {
        if((*list)->next == NULL) {
            removeStart(list);
        }
        else {
            Node *currentNode, *previousNode;
            currentNode = *list;
            while(currentNode->next != NULL) {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
            previousNode->next = NULL;
            currentNode->previous = NULL;
            free(currentNode);
        }
    }
}

int removeByValue(Node **list, int searchValue) {
    if(isListEmpty(list)) return 0;

     if((*list)->value == searchValue) {
        removeStart(list);
        return 1;
    }

    Node *previousNode, *currentNode;
    currentNode = *list;
    while(currentNode != NULL) {
        if(currentNode->value == searchValue) {
            previousNode->next = currentNode->next;
            currentNode->previous = NULL;
            currentNode->next = NULL;
            free(currentNode);
            return 1;
        }
        previousNode = currentNode;
        currentNode = currentNode->next;
    }

    return 2;
}

int getNodeValueByIndex(Node **list, int index) {
    if(index < 0) return NULL;

    Node *currentNode = *list;
    int aux = 0;

    while(aux != index && currentNode != NULL) {
        if(currentNode == NULL) return -1;
        currentNode = currentNode->next;
        aux++;
    }
    if(currentNode == NULL) return NULL;
    return currentNode->value;
}

int getNodeIndexByValue(Node **list, int searchValue) {
    if(isListEmpty(list)) return -1;

    Node *currentNode = *list;
    int index = 0;

    while(currentNode != NULL) {
        if(currentNode->value == searchValue) {
            return index;
        }
        currentNode = currentNode->next;
        index++;
    }

    return -2;
}

int getListSize(Node **list) {
    int acm = 0;
    Node *currentNode = *list;
    while(currentNode != NULL) {
        acm++;
        currentNode = currentNode->next;
    }
    return acm;
}

void printList(Node **list) {
    if(isListEmpty(list)) {
        printf("The list is empty!\n");
    } else {
        Node *currentNode = *list;
        while(currentNode != NULL) {
            printf("%d ", currentNode->value);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

void printListRecursively(Node **list) {
    Node *currentNode = *list;
    if(currentNode == NULL) {
        printf("\n");
        return;
    } 
    printf("%d ", currentNode->value);
    printListRecursively(&currentNode->next);
}

void printListBackwards(Node **list) {
    Node *currentNode = *list;
    if(currentNode->next != NULL) printListBackwards(&currentNode->next);
    if(currentNode->previous == NULL) printf("%d\n", currentNode->value);
    else printf("%d ", currentNode->value);
    return; 
} 