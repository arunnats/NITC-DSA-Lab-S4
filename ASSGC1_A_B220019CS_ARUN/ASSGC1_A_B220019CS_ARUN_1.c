#include <stdio.h>
#include <string.h>

struct Stack
{
    int arr[1001];
    int top;
};

void initialize(struct Stack *stack)
{
    stack->top = -1;
}

int isEmpty(struct Stack *stack)
{
    return stack->top == -1;
}

void push(struct Stack *stack, int element)
{
    stack->arr[++stack->top] = element;
}

int pop(struct Stack *stack)
{
    return stack->arr[stack->top--];
}

int hasDuplicateParentheses(char *expression)
{
    int len = strlen(expression);

    struct Stack stack;
    initialize(&stack);

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
