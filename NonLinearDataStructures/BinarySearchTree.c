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
bool isTreeEmpty(Node *root);
bool insertNode(Node **root, Node *newNode);
void printInOrder(Node *root);
void printPreOrder(Node *root);
void printPosOrder(Node *root);

int main() {
    Node *bst = NULL;
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
    return 0;
}

Node *createNode(int newKey) {
    Node *newNode = (Node *) malloc(sizeof(Node));
    newNode->key = newKey;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
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
