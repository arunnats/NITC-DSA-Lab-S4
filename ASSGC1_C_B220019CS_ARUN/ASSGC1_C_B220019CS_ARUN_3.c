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
    int groupNum = hashFunction(newStudent->firstName, newStudent->age);

    newStudent->next = map->list[groupNum];
    map->list[groupNum] = newStudent;
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

void displayCountAndNames(int count, struct Student *current)
{
    if (current != NULL)
    {
        displayCountAndNames(count - 1, current->next);
        printf("%s ", current->firstName);
    }
}

void displayCount(int groupNum, struct HashMap *map)
{
    int count = 0;
    struct Student *current = map->list[groupNum];

    while (current != NULL)
    {
        count++;
        current = current->next;
    }

    printf("%d ", count);

    displayCountAndNames(count, map->list[groupNum]);
}

void displayStudentList(int groupNum, struct HashMap *map)
{
    struct Student *current = map->list[groupNum];

    while (current != NULL)
    {
        printf("%s ", current->firstName);
        current = current->next;
    }

    printf("\n");
}

void displayBranchStudentList(int groupNum, char branch[], struct HashMap *map)
{
    struct Student *current = map->list[groupNum];
    int found = 0;

    while (current != NULL)
    {
        if (strcmp(current->branch, branch) == 0)
        {
            printf("%s ", current->firstName);
            found = 1;
        }
        current = current->next;
    }

    if (!found)
    {
        printf("-1\n");
    }
    else
    {
        printf("\n");
    }
}

int main()
{
    int n;
    scanf("%d", &n);

    struct HashMap map;
    initializeHashMap(&map);

    populateHashMap(&map, n);

    char option;
    do
    {
        scanf(" %c", &option);
        if (option != 'e')
        {
            if (option == 'c')
            {
                int k;
                scanf("%d", &k);
                displayCount(k, &map);
                printf("\n");
            }
            else
            {
                int m;
                char branch[3];
                if (scanf("%d", &m) == 1 && m >= 0 && m <= 3)
                {
                    displayStudentList(m, &map);
                }
                else
                {
                    printf("Invalid option or group number\n");
                }
            }
        }
    } while (option != 'e');

    return 0;
}