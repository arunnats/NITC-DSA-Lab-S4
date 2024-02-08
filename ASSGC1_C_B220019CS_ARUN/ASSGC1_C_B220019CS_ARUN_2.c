#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 100

struct Node
{
    int key;
    int value;
    struct Node *next;
    struct Node *prev;
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

int hashFunction(int key, int tableSize)
{
    return key % tableSize;
}

void insert(struct HashMap *map, int key, int value)
{
    int index = hashFunction(key);
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = map->array[index];
    map->array[index] = newNode;
}

int search(struct HashMap *map, int key)
{
    int index = hashFunction(key);
    struct Node *current = map->array[index];
}

int main()
{
    struct HashMap *map = createHashMap();
}
