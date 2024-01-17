#include <stdio.h>
#include <string.h>

// Stack structure
struct Stack
{
    int arr[1001];
    int top;
};

// Function to initialize the stack
void initialize(struct Stack *stack)
{
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(struct Stack *stack, int element)
{
    stack->arr[++stack->top] = element;
}

// Function to pop an element from the stack
int pop(struct Stack *stack)
{
    return stack->arr[stack->top--];
}

// Function to check for duplicate parentheses
int hasDuplicateParentheses(char *expression)
{
    int len = strlen(expression);

    // Initialize the stack
    struct Stack stack;
    initialize(&stack);

    for (int i = 0; i < len; i++)
    {
        if (expression[i] == '(')
        {
            // Push the index of the opening parenthesis
            push(&stack, i);
        }
        else if (expression[i] == ')')
        {
            if (!isEmpty(&stack))
            {
                // Pop the index of the matching opening parenthesis
                int openingIndex = pop(&stack);

                // Check for adjacent parentheses
                if (i - openingIndex == 1)
                {
                    return 1; // Duplicate parentheses found
                }
            }
        }
    }

    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);

    char expression[1001];
    scanf("%s", expression);

    int result = hasDuplicateParentheses(expression);

    printf("%d\n", result);

    return 0;
}
