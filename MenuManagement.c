#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct MENUE
{
    int id;
    int category;
    int price;
    char name[40];
    struct MENUE *next;
} MenuItem;

// New Item
typedef struct MENUEHEADER
{
    int categoryNumber;
    int NumberOfItem;
    char category[40];
    struct MENUE *items;
    struct MENUEHEADER *next;
} MenueHeader;
// End New Item

// typedef struct HeadTraker
// {
//     int maxId;
//     int NumberofCetogory;
//     MenueHeader *head;
// } ;

void PrintHeading(char str[])
{
    printf("\n======================================================================================\n");
    printf("\t\t\t\t%s ", str);
    printf("\n=======================================================================================\n");
};

void PrintError(char str[])
{
    printf("\n########################################################################################\n");
    printf("Error :- ");
    printf("\n########################################################################################\n");
    printf("%s", str);
    printf("\n----------------------------------------------------------------------------------------\n");
}

void LogMark()
{
    printf("\n----------------------------------------------------------------------------------------\n");
};

void setLength(char *str, int len)
{
    int j = 0;
    while (str[j] != '\0')
    {
        j++;
    }
    while (j < len - 1)
    {
        str[j] = ' ';
        j++;
    }
    str[j] = '\0';
}

void setItemNode(MenueHeader *HeadTraker, MenuItem *HeadPointer)
{

    MenuItem *trakItem;
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
}

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
                setLength(menueCategory->category, 40);
            }

            value = strtok(NULL, ", ");
            column++;
        }

        // printf("\n");
    }
    fclose(fp);

    return head;
};

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
                setLength(HeadPointer->name, 40);
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
        setItemNode(head, HeadPointer);
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
        printf("| ItemId\t| ItemName\t\t\t\t\t| ItemPrice");
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

void DisplayCetegory(MenueHeader *head)
{

    PrintHeading("Menue Cetegory");
    LogMark();
    printf("| CategoryID\t\t| CetorogyName");
    LogMark();
    while (head != NULL)
    {
        printf("| %d\t\t| %s\n", head->categoryNumber, head->category);
        head = head->next;
    }
};

void WriteDataToFile(MenueHeader *node, char *file1, char *file2)
{

    int column = 0, row = 0;
    char buffer[1024];
    char pre[] = "./Database/";
    char pre1[] = "./Database/";
    FILE *fp1 = fopen(strcat(pre, file1), "w");
    FILE *fp2 = fopen(strcat(pre1, file2), "w");
    fprintf(fp1, "number,CategoryName\n");
    fprintf(fp2, "ItemId,ItemCetogaory,ItemName,Price\n");
    MenuItem *temp = NULL;
    while (node != NULL)
    {
        fprintf(fp1, "%d,%s\n", node->categoryNumber, node->category);
        temp = node->items;
        while (temp != NULL)
        {
            fprintf(fp2, "%d,%d,%s,%d\n", temp->id, temp->category, temp->name, temp->price);
            temp = temp->next;
        }
        node = node->next;
    }

    fclose(fp1);
    fclose(fp2);
}
/*
New Added Item starts
 */

MenuItem *createMenueItem(MenueHeader *head)
{
    MenuItem *new = (MenuItem *)malloc(sizeof(MenuItem));
    DisplayCetegory(head);
    printf("select Cetogry :- ");
    scanf("%d", &new->category);

    printf("Enter Item Name :- ");
    gets(new->name);
    gets(new->name);
    setLength(new->name, 40);
    printf("Enter Item Price :- ");
    scanf("%d", &new->price);
    new->next = NULL;
    new->id = -1;

    return new;
};

void main()
{
    MenueHeader *start = getMenueHeadersFromFile("CategoryType.csv");
    MenueHeader *traker = NULL;
    getMenueItemFromFile("MenueItem.csv", start);
    DisplayMenue(start);
    printf("Pregram Runs");
    MenuItem *new = createMenueItem(start);
    setItemNode(start, new);
    DisplayMenue(start);
    WriteDataToFile(start, "CategoryType.csv", "MenueItem.csv");
}