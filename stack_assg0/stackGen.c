#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct
{
    int array[MAX_SIZE];
    int top;
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(Stack *stack)
{
    return stack->top == -1;
}

int isFull(Stack *stack)
{
    return stack->top == MAX_SIZE - 1;
}

void push(Stack *stack, int data)
{
    if (isFull(stack))
    {
        printf("Stack overflow!\n");
        return;
    }
    stack->array[++stack->top] = data;
}

int pop(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack underflow!\n");
        return -1;
    }
    return stack->array[stack->top--];
}

int peek(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty!\n");
        return -1;
    }
    return stack->array[stack->top];
}

void display(Stack *stack)
{
    if (isEmpty(stack))
    {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack elements: ");
    for (int i = stack->top; i >= 0; --i)
    {
        printf("%d ", stack->array[i]);
    }
    printf("\n");
}

int main()
{
    Stack *stack = createStack();

    push(stack, 1);
    push(stack, 2);
    push(stack, 3);

    display(stack);

    printf("Popped element: %d\n", pop(stack));
    printf("Top element: %d\n", peek(stack));

    display(stack);

    return 0;
}
