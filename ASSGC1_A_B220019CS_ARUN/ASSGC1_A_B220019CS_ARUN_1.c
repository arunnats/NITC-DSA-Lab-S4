#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 1000000

typedef struct
{
    char arr[MAX_SIZE];
    int top;
} Stack;

void push(Stack *s, char ch)
{
    if (s->top == MAX_SIZE - 1)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    s->arr[++(s->top)] = ch;
}

char pop(Stack *s)
{
    if (s->top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return s->arr[(s->top)--];
}

int duplicateParenthesis(char *expr, Stack *s)
{
    int i;
    int len = strlen(expr);

    for (i = 0; i < len; i++)
    {
        char ch = expr[i];
        if (ch == ')')
        {
            char top = pop(s);

            int elementsInside = 0;
            while (top != '(')
            {
                elementsInside++;
                top = pop(s);
            }

            if (elementsInside <= 1)
            {
                return 1;
            }
        }
        else
        {
            push(s, ch);
        }
    }

    return 0;
}

int main()
{
    int n;
    char expr[MAX_SIZE];

    scanf("%d", &n);
    scanf("%s", expr);

    Stack s;
    s.top = -1;

    int result = duplicateParenthesis(expr, &s);
    printf("%d\n", result);

    return 1;
}
