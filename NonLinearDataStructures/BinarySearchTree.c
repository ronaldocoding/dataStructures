#include <stdio.h>
#include <stdlib.h>
#define bool int
#define true 1
#define false 0

typedef struct Node {
    int key;
    struct Node *left;
    struct Node *right;
} Node;

Node *createNode(int newKey);
Node *binarySearch(Node *root, int searchedKey);
Node *searchNode(Node *root, int searchedKey, Node **nodeParent);
bool isTreeEmpty(Node *root);
bool insertNode(Node **root, Node *newNode);
void initializeTree(Node **root);
void destroyTreeAux(Node *root);
void destroyTree(Node **root, Node *rootParent);
void printInOrder(Node *root);
void printPreOrder(Node *root);
void printPosOrder(Node *root);
void printPreOrderWithParentheses(Node *root);

int main() {
    Node *bst;
    initializeTree(&bst);
    insertNode(&bst, createNode(49));
    insertNode(&bst, createNode(28));
    insertNode(&bst, createNode(83));
    insertNode(&bst, createNode(18));
    insertNode(&bst, createNode(40));
    insertNode(&bst, createNode(71));
    insertNode(&bst, createNode(97));
    insertNode(&bst, createNode(69));
    insertNode(&bst, createNode(72));
    insertNode(&bst, createNode(92));
    insertNode(&bst, createNode(99));
    insertNode(&bst, createNode(44));
    insertNode(&bst, createNode(32));
    insertNode(&bst, createNode(11));
    insertNode(&bst, createNode(19));
    printPosOrder(bst);
    printf("\n");
    printPreOrder(bst);
    printf("\n");
    printInOrder(bst);
    printf("\n");
    Node *searchedNode = binarySearch(bst, 71);
    printPreOrder(searchedNode);
    printf("\n");
    Node *nodeParent;
    Node *newSearchedNode = searchNode(bst, 83, &nodeParent);
    printPreOrder(newSearchedNode);
    printf("\n");
    printPreOrder(nodeParent);
    printf("\n");
    printPreOrderWithParentheses(bst);
    printf("\n");
    destroyTree(&newSearchedNode, bst);
    printPreOrder(bst);
    printf("\n");
    return 0;
}

Node *createNode(int newKey) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = newKey;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

Node *binarySearch(Node *root, int searchedKey) {
    if(isTreeEmpty(root)) {
        return NULL;
    } else {
        if(root->key == searchedKey) {
            return root;
        } else {
            if(searchedKey > root->key) {
                return binarySearch(root->right, searchedKey);
            } else {
                return binarySearch(root->left, searchedKey);
            }
        }
    }
}

Node *searchNode(Node *root, int searchedKey, Node **nodeParent) {
    *nodeParent = NULL;
    if(isTreeEmpty(root)) {
        return NULL;
    } else {
        Node *currentNode = root;
        while(currentNode != NULL) {
            if(currentNode->key == searchedKey) {
                return currentNode;
            } else {
                *nodeParent = currentNode;
                if(searchedKey > currentNode->key) {
                    currentNode = currentNode->right;
                } else {
                    currentNode = currentNode->left;
                }
            }
        }
    }
    return NULL;
}

bool isTreeEmpty(Node *root) {
    return root == NULL;
}

bool insertNode(Node **root, Node *newNode) {
    if(isTreeEmpty(*root)) {
        *root = newNode;
        return true;
    } else {
        if(newNode->key > (*root)->key) {
            if(isTreeEmpty((*root)->right)) {
                (*root)->right = newNode;
                return true;
            } else {
                return insertNode(&(*root)->right, newNode);
            }
        } else {
            if(isTreeEmpty((*root)->left)) {
                (*root)->left = newNode;
                return true;
            } else {
                return insertNode(&(*root)->left, newNode);
            }
        }
    }
}

void initializeTree(Node **root) {
    *root = NULL;
}

void destroyTreeAux(Node *root) {
    if(!isTreeEmpty(root)) {
        destroyTreeAux(root->left);
        destroyTreeAux(root->right);
        root->left = NULL;
        root->right = NULL;
        free(root);
    }
}

void destroyTree(Node **root, Node *rootParent) {
    destroyTreeAux(*root);
    Node *nodeParent;
    searchNode(rootParent, (*root)->key, &nodeParent);
    if(!isTreeEmpty(nodeParent)) {
        if(nodeParent->left == *root) nodeParent->left = NULL;
        else nodeParent->right = NULL;
    }
    *root = NULL;
}

void printInOrder(Node *root) {
    if(isTreeEmpty(root)) return;
    printInOrder(root->left);
    printf("%d ", root->key);
    printInOrder(root->right);
}

void printPreOrder(Node *root) {
    if(isTreeEmpty(root)) return;
    printf("%d ", root->key);
    printPreOrder(root->left);
    printPreOrder(root->right);
}

void printPosOrder(Node *root) {
    if(isTreeEmpty(root)) return;
    printPosOrder(root->left);
    printPosOrder(root->right);
    printf("%d ", root->key);
}

void printPreOrderWithParentheses(Node *root) {
    if(isTreeEmpty(root)) return;
    printf("%d ", root->key);
    printf(" (");
    printPreOrderWithParentheses(root->left);
    printPreOrderWithParentheses(root->right);
    printf(") ");
}
