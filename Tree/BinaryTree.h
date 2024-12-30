#ifndef BINARY_TREE_H
#define BINARY_TREE_H

#include <stdbool.h>

// Define the structure for a node in the binary tree
typedef struct Node
{
    int data;            // Data stored in the node
    struct Node *lchild; // Pointer to the left child
    struct Node *rchild; // Pointer to the right child
} Node;

// Define the structure for the binary tree
typedef struct BinaryTree
{
    Node *root; // Root of the binary tree
} BinaryTree;

// Queue structure for level-order traversal
typedef struct QueueNode
{
    Node *node;
    struct QueueNode *next;
} QueueNode;

// Queue structure to hold nodes for level-order traversal
typedef struct Queue
{
    QueueNode *front;
    QueueNode *rear;
} Queue;

// Function to create a binary tree with the given data
BinaryTree *createBinaryTree(int data);

// Function to add a node in the binary tree
BinaryTree *addNodeInBinaryTree(BinaryTree *tree, int data);

// Function to find the height of the binary tree
int findHeightOfBinaryTree(BinaryTree *tree);

// Recursive Traversals
void inOrderRecursiveTraversalOfBinaryTree(Node *tree);
void preOrderRecursiveTraversalOfBinaryTree(Node *tree);
void postOrderRecursiveTraversalOfBinaryTree(Node *tree);

// Non-Recursive Traversals
void inOrderNonRecursiveTraversalOfBinaryTree(Node *tree);
void preOrderNonRecursiveTraversalOfBinaryTree(Node *tree);
void postOrderNonRecursiveTraversalOfBinaryTree(Node *tree);

//
int height(Node *node);
//
Node *findMinNodeLeftRight(Node *node);
// Function to find the minimum value node in the binary tree
Node *findMinNode(BinaryTree *tree);

// Function to find the maximum value node in the binary tree
Node *findMaxNode(BinaryTree *tree);

// Function to count the total number of nodes in the binary tree
int countNodes(BinaryTree *tree);

// Function to perform a level-order (BFS) traversal of the binary tree
void levelOrderTraversal(BinaryTree *tree);

// Function to find the depth of a node in the binary tree
int findDepthOfNode(BinaryTree *tree, int data);

// Function to find a node with the given data
Node *findNodeWithData(BinaryTree *tree, int data);

// Function to delete a node with the given data
BinaryTree *deleteNodeWithData(BinaryTree *tree, int data);
// Function declaration for deleteNodeRecursive
Node *deleteNodeRecursive(Node *root, int data);
// Function declarations for the missing functions
Queue *createQueue();
void enqueue(Queue *q, Node *node);
Node *dequeue(Queue *q);
void freeQueue(Queue *q);
int balanceFactor(Node *node);
// Function to check if the binary tree is balanced
bool checkThatBinaryTreeIsBalancedBinaryTree(BinaryTree *tree);

// Function to create a new node with the given data
Node *createNode(int data);

// Function to display the elements of the tree (in-order traversal)
void showTreeElements(Node *root);

// Function to delete the binary tree and free memory
void deleteBinaryTree(BinaryTree *tree);

#endif // BINARY_TREE_H
