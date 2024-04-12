#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct Node
{
    char key[50];
    int value;
    struct Node *next;
};

struct HashMap
{
    struct Node *array[SIZE];
};

struct HashMap *createHashMap()
{
    struct HashMap *map = (struct HashMap *)malloc(sizeof(struct HashMap));
    for (int i = 0; i < SIZE; i++)
    {
        map->array[i] = NULL;
    }
    return map;
}

int hashFunction(char *key)
{
    int hash = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        hash += key[i];
    }
    return hash % SIZE;
}

void insert(struct HashMap *map, char *key, int value)
{
    int index = hashFunction(key);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = map->array[index];
    map->array[index] = newNode;
}

int search(struct HashMap *map, char *key)
{
    int index = hashFunction(key);
    struct Node *current = map->array[index];
    while (current != NULL)
    {
        if (strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    return -1;
}

int main()
{
    struct HashMap *map = createHashMap();

    insert(map, "Arun", 220019);
    insert(map, "Hafeez", 220030);
    insert(map, "Shindu", 220064);

    printf("Value for 'Arun': %d\n", search(map, "Arun"));
    printf("Value for 'Hafeez': %d\n", search(map, "Hafeez"));
    printf("Value for 'Alen': %d\n", search(map, "Alen"));

    return 0;
}
