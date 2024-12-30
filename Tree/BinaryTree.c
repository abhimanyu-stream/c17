#include "BinaryTree.h"
#include <stdio.h>
#include <stdlib.h>

// Function to create a binary tree with the given data
BinaryTree *createBinaryTree(int data)
{
    BinaryTree *tree = (BinaryTree *)malloc(sizeof(BinaryTree));
    tree->root = createNode(data);
    return tree;
}

// Function to create a new node with the given data
Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->lchild = NULL;
    newNode->rchild = NULL;
    return newNode;
}

// Function to add a node in the binary tree
BinaryTree *addNodeInBinaryTree(BinaryTree *tree, int data)
{
    if (tree == NULL)
    {
        return NULL;
    }

    Node *newNode = createNode(data);
    Node *current = tree->root;
    Node *parent = NULL;

    // Find the correct spot for the new node
    while (current != NULL)
    {
        parent = current;
        if (data < current->data)
        {
            current = current->lchild;
        }
        else
        {
            current = current->rchild;
        }
    }

    // Insert the new node as a child of the parent
    if (data < parent->data)
    {
        parent->lchild = newNode;
    }
    else
    {
        parent->rchild = newNode;
    }

    return tree;
}

// Recursive in-order traversal of the binary tree
void inOrderRecursiveTraversalOfBinaryTree(Node *node)
{
    if (node != NULL)
    {
        inOrderRecursiveTraversalOfBinaryTree(node->lchild); // Visit left child
        printf("%d ", node->data);                           // Visit current node
        inOrderRecursiveTraversalOfBinaryTree(node->rchild); // Visit right child
    }
}

// Recursive pre-order traversal of the binary tree
void preOrderRecursiveTraversalOfBinaryTree(Node *node)
{
    if (node == NULL)
        return;

    printf("%d ", node->data);                            // Visit current node
    preOrderRecursiveTraversalOfBinaryTree(node->lchild); // Visit left child
    preOrderRecursiveTraversalOfBinaryTree(node->rchild); // Visit right child
}

// Recursive post-order traversal of the binary tree
void postOrderRecursiveTraversalOfBinaryTree(Node *node)
{
    if (node == NULL)
        return;

    postOrderRecursiveTraversalOfBinaryTree(node->lchild); // Visit left child
    postOrderRecursiveTraversalOfBinaryTree(node->rchild); // Visit right child
    printf("%d ", node->data);                             // Visit current node
}

// Find a node with the given data
Node *findNodeWithData(BinaryTree *tree, int data)
{
    Node *current = tree->root;
    while (current != NULL)
    {
        if (current->data == data)
            return current;
        else if (data < current->data)
            current = current->lchild;
        else
            current = current->rchild;
    }
    return NULL;
}

// Function to delete a node with the given data
// Function to delete a node with the given data
BinaryTree *deleteNodeWithData(BinaryTree *tree, int data)
{
    if (tree == NULL || tree->root == NULL)
        return tree;

    tree->root = deleteNodeRecursive(tree->root, data);
    return tree;
}

// Helper function to delete a node recursively
Node *deleteNodeRecursive(Node *root, int data)
{
    // If the tree is empty
    if (root == NULL)
        return root;

    // Recur down the tree to find the node to be deleted
    if (data < root->data)
    {
        root->lchild = deleteNodeRecursive(root->lchild, data); // Go to the left subtree
    }
    else if (data > root->data)
    {
        root->rchild = deleteNodeRecursive(root->rchild, data); // Go to the right subtree
    }
    else
    {
        // Node to be deleted found

        // Case 1: Node has no children (leaf node)
        if (root->lchild == NULL && root->rchild == NULL)
        {
            free(root); // Deallocate memory
            return NULL;
        }
        // Case 2: Node has one child
        else if (root->lchild == NULL)
        {
            Node *temp = root->rchild;
            free(root);
            return temp; // Return the non-NULL child
        }
        else if (root->rchild == NULL)
        {
            Node *temp = root->lchild;
            free(root);
            return temp; // Return the non-NULL child
        }
        // Case 3: Node has two children
        else
        {
            // Get the in-order successor (smallest in the right subtree)
            Node *temp = findMinNodeLeftRight(root->rchild); // Use the new findMinNode function

            // Copy the in-order successor's data to the current node
            root->data = temp->data;

            // Delete the in-order successor
            root->rchild = deleteNodeRecursive(root->rchild, temp->data);
        }
    }

    return root;
}
// Function to find the minimum value node in a given subtree (starting from a node)
Node *findMinNodeLeftRight(Node *node)
{
    // If the node is NULL, return NULL
    if (node == NULL)
        return NULL;

    // Traverse to the leftmost node (the minimum in a binary search tree)
    while (node->lchild != NULL)
    {
        node = node->lchild;
    }

    return node;
}
// Function to find the minimum value node in the binary tree
Node *findMinNode(BinaryTree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;
    Node *current = tree->root;
    while (current->lchild != NULL)
    {
        current = current->lchild;
    }
    return current;
}

// Function to find the maximum value node in the binary tree
Node *findMaxNode(BinaryTree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return NULL;
    Node *current = tree->root;
    while (current->rchild != NULL)
    {
        current = current->rchild;
    }
    return current;
}

// Helper function to count nodes recursively
int countHelper(Node *node)
{
    if (node == NULL)
        return 0; // If the node is NULL, it contributes 0 to the count

    // Recursively count the left and right subtrees and add 1 for the current node
    return 1 + countHelper(node->lchild) + countHelper(node->rchild);
}

// Function to count the total number of nodes in the binary tree
int countNodes(BinaryTree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return 0; // If the tree is empty, return 0

    return countHelper(tree->root); // Call the helper function on the root
}
// Queue-related function implementations in BinaryTree.c

Queue *createQueue()
{
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->front = q->rear = NULL;
    return q;
}

void enqueue(Queue *q, Node *node)
{
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->node = node;
    newNode->next = NULL;

    if (q->rear == NULL)
    {
        q->front = q->rear = newNode;
        return;
    }

    q->rear->next = newNode;
    q->rear = newNode;
}

Node *dequeue(Queue *q)
{
    if (q->front == NULL)
        return NULL;

    QueueNode *temp = q->front;
    Node *node = temp->node;
    q->front = q->front->next;

    if (q->front == NULL)
        q->rear = NULL;

    free(temp);
    return node;
}

void freeQueue(Queue *q)
{
    QueueNode *current = q->front;
    while (current != NULL)
    {
        QueueNode *temp = current;
        current = current->next;
        free(temp);
    }
    free(q);
}

// Function to perform a level-order (BFS) traversal of the binary tree
void levelOrderTraversal(BinaryTree *tree)
{
    if (tree == NULL || tree->root == NULL)
        return;

    Queue *q = createQueue(); // Now knows about createQueue
    enqueue(q, tree->root);   // Now knows about enqueue

    while (q->front != NULL)
    {
        Node *current = dequeue(q); // Now knows about dequeue
        printf("%d ", current->data);

        if (current->lchild != NULL)
            enqueue(q, current->lchild);
        if (current->rchild != NULL)
            enqueue(q, current->rchild);
    }
    printf("\n");

    // Free the queue memory after traversal is complete
    freeQueue(q); // Now knows about freeQueue
}

// Check if the binary tree is balanced
bool checkThatBinaryTreeIsBalancedBinaryTree(BinaryTree *tree)
{
    return (balanceFactor(tree->root) <= 1 && balanceFactor(tree->root) >= -1); // Now knows about balanceFactor
}

int balanceFactor(Node *node)
{
    return height(node->lchild) - height(node->rchild);
}
// Function to find the depth of a node in the binary tree
int findDepthOfNode(BinaryTree *tree, int data)
{
    if (tree == NULL || tree->root == NULL)
        return -1;

    int depth = 0;
    Node *current = tree->root;

    while (current != NULL)
    {
        if (data == current->data)
            return depth;
        else if (data < current->data)
        {
            current = current->lchild;
            depth++;
        }
        else
        {
            current = current->rchild;
            depth++;
        }
    }

    return -1; // Node not found
}

void showTreeElements(Node *root)
{
    if (root == NULL)
        return;
    showTreeElements(root->lchild);
    printf("%d ", root->data);
    showTreeElements(root->rchild);
}

// Helper function to compute height recursively
int height(Node *node)
{
    if (node == NULL)
    {
        return -1; // Return -1 for null nodes to count edges
    }
    int leftHeight = height(node->lchild);
    int rightHeight = height(node->rchild);
    return (leftHeight > rightHeight ? leftHeight : rightHeight) + 1;
}

// Function to find the height of the binary tree
int findHeightOfBinaryTree(BinaryTree *tree)
{
    return height(tree->root);
}

//

// Recursive function to delete all nodes
void deleteNodes(Node *node)
{
    if (node == NULL)
        return;
    deleteNodes(node->lchild);
    deleteNodes(node->rchild);
    free(node);
}

// Function to delete the binary tree and free memory
void deleteBinaryTree(BinaryTree *tree)
{
    if (tree == NULL)
        return;
    deleteNodes(tree->root);
    free(tree);
}
