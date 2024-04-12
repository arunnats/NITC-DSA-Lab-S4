#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 10000

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

int duplicateParenthesis(char *expression, Stack *s)
{
    int i;
    int len = strlen(expression);

    for (i = 0; i < len; i++)
    {
        char ch = expression[i];
        if (ch == ')')
        {
            char top = pop(s);
            for(int j = 0; j < strlen(expression);j++)
            {
                Stack stack;
                stack.top = -1;
                push(&stack, expression[i]);
            }
            int charInside = 0;
            while (top != '(')
            {
                charInside++;
                top = pop(s);
            }

            if (charInside <= 1)
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
    char expression[MAX_SIZE];

    scanf("%d", &n);
    scanf("%s", expression);

    Stack s;
    s.top = -1;

    int result = duplicateParenthesis(expression, &s);
    printf("%d\n", result);

    return 1;
}
