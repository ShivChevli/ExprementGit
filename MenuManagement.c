#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
/*
Repeted File
 */
typedef struct BUINDINGNODE
{
    int number;
    char bindValue[20];
    struct BUINDINGNODE *next;
} Bind;

typedef struct BINDHEADE
{
    Bind *userType;
    Bind *categoryType;
} MapHeadNode;

typedef struct MENUE
{
    int id;
    int category;
    int price;
    char name[20];
    struct MENUE *next;
} MenuItem;

// New Item
typedef struct MENUEHEADER
{
    int categoryNumber;
    char category[20];
    struct MENUE *items;
    struct MENUEHEADER *next;
} MenueHeader;
// End New Item

void PrintHeading(char str[])
{
    printf("\n===========================================================\n");
    printf("\t\t%s \n", str);
    printf("===========================================================\n");
};

void PrintError(char str[])
{
    printf("\n##########################################################\n");
    printf("Error :- ");
    printf("\n##########################################################\n");
    printf("%s", str);
    printf("\n-----------------------------------------------------------\n");
}

void LogMark()
{
    printf("\n-----------------------------------------------------------\n");
};

MenueHeader *getMenueHeadersFromFile(char file[])
{

    // File Headaling Pointers
    int column = 0, row = 0;
    char buffer[1024];
    char pre[] = "./Database/";
    FILE *fp = fopen(strcat(pre, file), "ra");

    MenueHeader *head = NULL;
    MenueHeader *menueCategory = (MenueHeader *)malloc(sizeof(MenueHeader));

    while (fgets(buffer, 1024, fp))
    {
        row++;
        if (row == 1)
        {
            continue;
        }

        char *value = strtok(buffer, ", ");

        if (head == NULL)
        {
            head = menueCategory;
        }
        else
        {
            menueCategory->next = (MenueHeader *)malloc(sizeof(MenueHeader));
            menueCategory = menueCategory->next;
        }
        menueCategory->next = NULL;
        menueCategory->items = NULL;
        column = 0;
        while (value)
        {
            value[strcspn(value, "\n")] = '\0';

            // Column 1
            if (column == 0)
            {
                // printf("User Id :");
                menueCategory->categoryNumber = atoi(value);
            }

            // Column 2
            if (column == 1)
            {
                strcpy(menueCategory->category, value);
            }

            value = strtok(NULL, ", ");
            column++;
        }

        // printf("\n");
    }
    fclose(fp);

    return head;
};

/*
New Added Item starts
 */
void *getMenueItemFromFile(char file[], MenueHeader *head)
{

    // File Headaling Pointers
    int column = 0, row = 0;
    char buffer[1024];
    // FILE *fp = fopen(file, "ra");
    char pre[] = "./Database/";
    FILE *fp = fopen(strcat(pre, file), "ra");

    if (fp == NULL)
    {
        printf("FIle NOt Open\n");
    }
    else
    {
        PrintError("FIle Exiest");
    }
    MenueHeader *HeadTraker = NULL;
    MenuItem *HeadPointer = NULL;
    MenuItem *trakItem = NULL;

    while (fgets(buffer, 1024, fp))
    {
        HeadTraker = head;
        row++;
        if (row == 1)
        {
            continue;
        }

        char *value = strtok(buffer, ",");
        value[strcspn(value, "\n")] = '\0';
        HeadPointer = (MenuItem *)malloc(sizeof(MenuItem));
        HeadPointer->next = NULL;

        column = 0;
        while (value)
        {
            // Column 1
            if (column == 0)
            {
                // printf("User Id :");
                HeadPointer->id = atoi(value);
            }

            // Column 2
            if (column == 1)
            {
                // printf("\tUser Type :");
                HeadPointer->category = atoi(value);
            }

            // Column 4
            if (column == 2)
            {
                strcpy(HeadPointer->name, value);
                // printf("\t\tUser Name :");
            }

            if (column == 3)
            {
                HeadPointer->price = atoi(value);
                // printf("\t\tUser Password :");
            }

            // printf("%s", value);
            value = strtok(NULL, ",");
            column++;
        }

        printf("%d\t%d\t%s\t%d\n", HeadPointer->id, HeadPointer->category, HeadPointer->name, HeadPointer->price);
        /*
            Put nodes in Category Link list
        */
        while (HeadTraker->categoryNumber != HeadPointer->category)
        {
            HeadTraker = HeadTraker->next;
        }

        if (HeadTraker->items == NULL)
        {
            HeadTraker->items = HeadPointer;
        }
        else
        {

            trakItem = HeadTraker->items;
            while (trakItem->next != NULL)
            {
                trakItem = trakItem->next;
            }
            trakItem->next = HeadPointer;
        }

        // printf("\n");
    }
    fclose(fp);
};

void DisplayMenue(MenueHeader *start)
{

    MenuItem *track = NULL;
    while (start != NULL)
    {
        // LogMark();
        // printf("\t\t%s", start->category);
        PrintHeading(start->category);
        track = start->items;
        LogMark();
        printf("| ItemId\t| ItemName\t| ItemPrice");
        LogMark();
        while (track != NULL)
        {
            printf("| %d\t\t| %s\t| %d Rs\n", track->id, track->name, track->price);
            track = track->next;
        }
        start = start->next;
    }
    printf("Exit");
}

void main()
{
    MenueHeader *start = getMenueHeadersFromFile("CategoryType.csv");
    getMenueItemFromFile("MenueItem.csv", start);
    DisplayMenue(start);
    printf("Pregram Runs");
}