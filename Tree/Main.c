#include "BinaryTree.h"
#include <stdio.h>

int main()
{
    // Create a binary tree
    BinaryTree *tree = createBinaryTree(10);

    // Add nodes to the tree
    addNodeInBinaryTree(tree, 5);
    addNodeInBinaryTree(tree, 15);
    addNodeInBinaryTree(tree, 2);
    addNodeInBinaryTree(tree, 7);

    // Display tree elements (in-order traversal)
    printf("Tree elements (in-order): ");
    showTreeElements(tree->root);
    printf("\n");

    // Find the height of the tree
    printf("Height of the tree: %d\n", findHeightOfBinaryTree(tree));

    printf("\n");

    // Check if the tree is balanced
    printf("Is the tree balanced? %s\n", checkThatBinaryTreeIsBalancedBinaryTree(tree) ? "Yes" : "No");

    // Delete the binary tree
    deleteBinaryTree(tree);

    return 0;
}
