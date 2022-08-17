#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node *next;
} Node;

Node * createNode(int newValue);
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

int main() {
    // TODO
}

Node * createNode(int newValue) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->value = newValue;
    newNode->next = NULL;
    return newNode;
}

int isListEmpty(Node **list) {
    if(*list == NULL) return 1;
    return 0;
}

void insertStart(Node **list, int newValue) {
    Node *newNode = createNode(newValue);
    if(isListEmpty(list)) {
        *list = newNode;
    }
    else {
        newNode->next = *list;
        *list = newNode;
    }
}

void insertMiddle(Node **list, int newValue, int index) {
    if(isListEmpty(list) || index <= 0) {
        insertStart(list, newValue);
    } 
    else {
        Node *previousNode, *currentNode, *newNode;
        currentNode = previousNode = *list;
        newNode = createNode(newValue);

        int aux = 0;
        while(aux != index && currentNode != NULL) {
            previousNode = currentNode;
            currentNode = currentNode->next;
            aux++;
        }

        previousNode->next = newNode;
        newNode->next = currentNode;
    }
}

void insertEnd(Node **list, int newValue) {
    if(isListEmpty(list)) {
        insertStart(list, newValue);
    } else {
        Node *currentNode, *newNode;
        currentNode = *list;
        newNode = createNode(newValue);
        while(currentNode->next != NULL) currentNode = currentNode->next;
        currentNode->next = newNode;
    }
}

void removeStart(Node **list) {
    if(!isListEmpty(list)) {
        Node *oldFirstNode = *list;
        *list = (*list)->next;
        free(oldFirstNode);
    }
}

void removeMiddle(Node **list, int index) {
    if(!isListEmpty(list)) {
        if(index <= 0) {
            removeStart(list);
        }
        else {
            Node *previousNode, *currentNode;
            currentNode = previousNode = *list;

            int aux = 0;
            while(aux != index && currentNode != NULL) {
                previousNode = currentNode;
                currentNode = currentNode->next;
                aux++;
            }

            if(currentNode != NULL) previousNode->next = currentNode->next;
            else removeEnd(list);
            free(currentNode);
        }
    }
}

void removeEnd(Node **list) {
    if(!isListEmpty(list)) {
        if((*list)->next == NULL) {
            removeStart(list);
        }
        else {
            Node *previousNode, *currentNode; 
            currentNode = *list;
            while(currentNode->next != NULL) {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
            previousNode->next = NULL;
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
    currentNode = previousNode = *list;

    while(currentNode != NULL) {
        if(currentNode->value == searchValue) {
            previousNode->next = currentNode->next;
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
    Node *currentNode = *list;
    while(currentNode != NULL) {
        printf("%d ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("\n");
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
    printf("%d ", currentNode->value);
    return; 
} 
