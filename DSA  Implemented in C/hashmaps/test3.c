#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
    char name[100];
    char branch[3];
    struct node *next;
};

typedef struct node node;

node *create_node(char *name, char *branch)
{
    node *newnode = (node *)malloc(sizeof(node));
    strcpy(newnode->name, name);
    strcpy(newnode->branch, branch);
    newnode->next = NULL;
    return newnode;
}

int hash_value(char *name, int age)
{
    int sum = 0;
    int i = 0;

    while (i < strlen(name))
    {
        sum += name[i++];
    }

    return (sum + age) % 4;
}

void insert(node **hash_table, char *name, char *branch, int age)
{
    int index = hash_value(name, age);
    node *newnode = create_node(name, branch);

    if (hash_table[index] == NULL)
    {
        hash_table[index] = newnode;
    }

    else
    {
        node *temp = hash_table[index];

        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newnode;
    }
}

void print_count(node **hash_table, int index)
{
    node *temp = hash_table[index];
    int count = 0;

    if (temp == NULL)
        printf("%d\n", count);

    else
    {
        while (temp != NULL)
        {
            count++;
            temp = temp->next;
        }
        printf("%d ", count);
        temp = hash_table[index];

        while (temp != NULL)
        {
            printf("%s ", temp->name);
            temp = temp->next;
        }
        printf("\n");
    }
}

void print_branch(node **hash_table, int index, char *branch)
{
    node *temp = hash_table[index];
    int count = 0;
    if (temp == NULL)
        printf("%d\n", -1);
    else
    {
        while (temp != NULL)
        {
            if (!strcmp(branch, temp->branch))
            {
                printf("%s ", temp->name);
                count++;
            }
            temp = temp->next;
        }
        if (count == 0)
            printf("%d\n", -1);
        else
            printf("\n");
    }
}

int main()
{
    char name[100];
    char Roll_no[10];
    char branch[3];
    char option;
    int index;

    int n, age;
    scanf("%d", &n);
    node *hash_table[4];

    for (int i = 0; i < 4; i++)
    {
        hash_table[i] = NULL;
    }

    int i = 0;

    while (i < n)
    {
        scanf("%s %s %d", name, Roll_no, &age);
        strncpy(branch, &Roll_no[7], 2);
        insert(hash_table, name, branch, age);
        i++;
    }

    while (1)
    {
        scanf("%c", &option);

        switch (option)
        {
        case 'c':
        {
            scanf(" %d", &index);
            print_count(hash_table, index);
            break;
        }

        case '0':
        {
            scanf(" %s", branch);
            print_branch(hash_table, 0, branch);
            break;
        }

        case '1':
        {
            scanf(" %s", branch);
            print_branch(hash_table, 1, branch);
            break;
        }

        case '2':
        {
            scanf(" %s", branch);
            print_branch(hash_table, 2, branch);
            break;
        }

        case '3':
        {
            scanf(" %s", branch);
            print_branch(hash_table, 3, branch);
            break;
        }

        case 'e':
            return 0;
        }
    }
}