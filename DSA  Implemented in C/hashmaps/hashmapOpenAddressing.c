#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100
#define EMPTY -1

struct Node
{
    char key[50];
    int value;
};

struct HashMap
{
    struct Node *array[SIZE];
};

unsigned int hashFunction(char *key)
{
    unsigned int hash = 0;
    for (int i = 0; key[i] != '\0'; i++)
    {
        hash = 31 * hash + key[i];
    }
    return hash % SIZE;
}

struct HashMap *createHashmap()
{
    struct HashMap *map = (struct HashMap *)malloc(sizeof(struct HashMap));
    for (int i = 0; i < SIZE; i++)
    {
        map->array[i] == NULL;
    }
    return map;
}

void insertLinear(struct HashMap *map, char *key, int value)
{
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->value = value;

    unsigned int index = hashFunction(key);
    while (map->array[index] != NULL && map->array[index] != (struct Node *)EMPTY)
    {
        index = (index + 1) % SIZE;
    }

    map->array[index] = newNode;
}

int search(struct HashMap *map, char *key)
{
    unsigned int index = hashFunction(key);
    while (map->array[index] != NULL)
    {
        if (strcmp(map->array[index]->key, key) == 0)
        {
            return map->array[index]->value;
        }
        index = (index + 1) % SIZE;
    }
    return -1;
}

int main()
{
    struct HashMap *map = createHashmap();

    insertLinear(map, "Arun", 220019);
    insertLinear(map, "Hafeez", 220030);
    insertLinear(map, "Shindu", 220064);

    printf("Value for 'Arun': %d\n", search(map, "Arun"));
    printf("Value for 'Hafeez': %d\n", search(map, "Hafeez"));
    printf("Value for 'Alen': %d\n", search(map, "Alen"));

    return 0;
}
