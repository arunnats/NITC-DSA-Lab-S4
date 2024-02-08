#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student
{
    char firstName[30];
    char rollNumber[20];
    int age;
    char branch[3];
    struct Student *next;
};

struct HashMap
{
    struct Student *list[4];
};

int hashFunction(char firstName[], int age)
{
    int sum = 0;
    for (int i = 0; i < strlen(firstName); i++)
    {
        sum += (int)firstName[i];
    }
    return (sum + age) % 4;
}

void initializeHashMap(struct HashMap *map)
{
    for (int i = 0; i < 4; i++)
    {
        map->list[i] = NULL;
    }
}

void insertStudent(struct Student *newStudent, struct HashMap *map)
{
    int groupIndex = hashFunction(newStudent->firstName, newStudent->age);

    newStudent->next = map->list[groupIndex];
    map->list[groupIndex] = newStudent;
}

void populateHashMap(struct HashMap *map, int n)
{
    for (int i = 0; i < n; i++)
    {
        struct Student *newStudent = (struct Student *)malloc(sizeof(struct Student));
        scanf("%s %s %d", newStudent->firstName, newStudent->rollNumber, &newStudent->age);
        newStudent->branch[0] = newStudent->rollNumber[9];
        newStudent->branch[1] = newStudent->rollNumber[10];
        newStudent->branch[2] = '\0';
        insertStudent(newStudent, map);
    }
}

int main()
{
    int n;
    scanf("%d", &n);

        return 1;
}