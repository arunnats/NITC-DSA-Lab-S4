#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 1000001

char stack[MAX_SIZE];
int top = -1;

void push(char ch)
{
    if (top == MAX_SIZE - 1)
    {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = ch;
}

char pop()
{
    if (top == -1)
    {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int hasDuplicateParenthesis(char *expr)
{
    int i;
    for (i = 0; expr[i]; i++)
    {
        char ch = expr[i];
        if (ch == ')')
        {
            int count = 0;
            while (top != -1 && stack[top] != '(')
            {
                pop();
                count++;
            }
            pop();
            if (count == 0 && (top != -1 && (stack[top] >= 'a' && stack[top] <= 'z')))
            {
                return 1;
            }
            else if (count == 0 || stack[top] == ')')
            {
                return 1;
            }
        }
        else
        {
            push(ch);
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

    int result = hasDuplicateParenthesis(expr);
    printf("%d\n", result);

    return 0;
}
