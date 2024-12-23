#include <stdio.h>
#include <stdlib.h>

// Define a Node for the linked list
typedef struct Node
{
    int data;
    struct Node *next;
} Node;

// Define a LinkedList structure
typedef struct LinkedList
{
    Node *head;
} LinkedList;

// Define a Stack structure (using linked list as the underlying data structure)
typedef struct Stack
{
    Node *top;
} Stack;

// Function prototypes
Node *create_node(int data);
void linked_list_insert_front(LinkedList *list, int data);
void linked_list_display(const LinkedList *list);
void stack_push(Stack *stack, int data);
int stack_pop(Stack *stack);
int stack_peek(const Stack *stack);
void stack_display(const Stack *stack);
void cleanup_linked_list(LinkedList *list);
void cleanup_stack(Stack *stack);

int main()
{
    printf("Hello World struct in C program\n");

    // Working with LinkedList
    LinkedList list = {NULL};
    linked_list_insert_front(&list, 10);
    linked_list_insert_front(&list, 20);
    linked_list_insert_front(&list, 30);
    printf("Linked List Contents:\n");
    linked_list_display(&list);

    // Cleanup linked list
    cleanup_linked_list(&list);

    // Working with Stack
    Stack stack = {NULL};
    stack_push(&stack, 5);
    stack_push(&stack, 15);
    stack_push(&stack, 25);
    printf("\nStack Contents (Top to Bottom):\n");
    stack_display(&stack);

    printf("\nPopped element: %d\n", stack_pop(&stack));
    printf("Stack Contents after Pop:\n");
    stack_display(&stack);

    // Cleanup stack
    cleanup_stack(&stack);

    return 0;
}

// Create a new node
Node *create_node(int data)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (!new_node)
    {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->data = data;
    new_node->next = NULL;
    return new_node;
}

// Insert a new node at the front of the linked list
void linked_list_insert_front(LinkedList *list, int data)
{
    Node *new_node = create_node(data);
    new_node->next = list->head;
    list->head = new_node;
}

// Display the contents of the linked list
void linked_list_display(const LinkedList *list)
{
    Node *current = list->head;
    while (current)
    {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

// Push an element onto the stack
void stack_push(Stack *stack, int data)
{
    Node *new_node = create_node(data);
    new_node->next = stack->top;
    stack->top = new_node;
}

// Pop an element from the stack
int stack_pop(Stack *stack)
{
    if (!stack->top)
    {
        fprintf(stderr, "Stack underflow\n");
        exit(EXIT_FAILURE);
    }
    Node *temp = stack->top;
    int data = temp->data;
    stack->top = temp->next;
    free(temp);
    return data;
}

// Peek at the top element of the stack
int stack_peek(const Stack *stack)
{
    if (!stack->top)
    {
        fprintf(stderr, "Stack is empty\n");
        exit(EXIT_FAILURE);
    }
    return stack->top->data;
}

// Display the contents of the stack
void stack_display(const Stack *stack)
{
    Node *current = stack->top;
    while (current)
    {
        printf("%d\n", current->data);
        current = current->next;
    }
}

// Cleanup the linked list and free memory
void cleanup_linked_list(LinkedList *list)
{
    Node *current = list->head;
    while (current)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
}

// Cleanup the stack and free memory
void cleanup_stack(Stack *stack)
{
    Node *current = stack->top;
    while (current)
    {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    stack->top = NULL;
}