#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
    Custom Data Structure
    TO store Menue Item
*/
typedef struct MENUE
{
    int id;
    int category;
    int price;
    char name[40];
    struct MENUE *next;
} MenuItem;

/*
    Custom Data Structure
    TO store Menue Cetegory and It's Items
*/
typedef struct MENUEHEADER
{
    int categoryNumber;
    int NumberOfItem;
    char category[40];
    struct MENUE *items;
    struct MENUEHEADER *next;
} MenueCategory;

/*
    Custom Data Structure
    TO stor Mata Data of Menue
    Use for Internal Tracking
*/
typedef struct CONTAINER
{
    int MaxId;
    int NumberofCetogory;
    MenueCategory *Start;
} Storage;

/*
    Custom Data Structure
    To Create Order
*/
typedef struct ORDERITEM
{
    MenuItem *item;
    int quantity, itemTotal;
    struct ORDERITEM *next;
} OrderItem;

typedef struct ORDER
{
    int total, totalItem, id;
    OrderItem *items;
} Order;

/*
    This is Utility Function Use for Print Heading and Look output formating Better
    Dependancies :- None
    DataStructure Used :- None
*/
void PrintHeading(char str[])
{
    printf("\n======================================================================================\n");
    printf("\t\t\t\t%s ", str);
    printf("\n=======================================================================================\n");
};

/*
    This is Utility Function Use for Display Error Messages.
    Dependancies :- None
    DataStructure Used :- None
*/
void PrintError(char str[])
{
    printf("\n########################################################################################\n");
    printf("Error :- ");
    printf("\n########################################################################################\n");
    printf("%s", str);
    printf("\n----------------------------------------------------------------------------------------\n");
}

/*
    This is Utility Function Use for Formating Output
    Dependancies :- None
    DataStructure Used :- None
*/
void LogMark()
{
    printf("\n----------------------------------------------------------------------------------------\n");
};

/*
    This is Utility Function User for Add Extra Space in String To look Formating Batter
    Dependancies :- None
    DataStructure Used :- None
*/
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

/*
    This is Utility Function User for Remove Extra Space in String To look Formating Batter
    Dependancies :- None
    DataStructure Used :- None
*/
void removeLength(char str[])
{
    int i = 0;
    for (i = 0; i < 20; i++)
    {
        if (str[i] == ' ' && str[i + 1] == ' ')
        {
            str[i] = '\0';
            break;
        }
    }
}

/*
    this Function Place Menue Item Node into Proper place in Link list
    Dependancies :- setItemNode Function,setLength Function
    DataStructure Used :- MenueCategory, MenuItem
*/
void setItemNode(MenueCategory *HeadTraker, MenuItem *HeadPointer)
{

    MenuItem *trakItem = NULL;
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

/*
    Read Menue Cetegory from File
    Dependancies :- setLength Function
    DataStructure Used :- MenueCategory, Storage
*/
Storage *getMenueCategorysFromFile(char file[])
{

    // File Headaling Pointers
    int column = 0, row = 0;
    char buffer[1024];
    char pre[] = "./Database/";
    FILE *fp = fopen(strcat(pre, file), "ra");

    Storage *head = (Storage *)malloc(sizeof(Storage));
    head->Start = NULL;
    MenueCategory *menueCategory = (MenueCategory *)malloc(sizeof(MenueCategory));

    while (fgets(buffer, 1024, fp))
    {
        row++;
        if (row == 1)
        {
            continue;
        }

        char *value = strtok(buffer, ", ");

        if (head->Start == NULL)
        {
            head->Start = menueCategory;
        }
        else
        {
            menueCategory->next = (MenueCategory *)malloc(sizeof(MenueCategory));
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
    head->NumberofCetogory = row;
    head->MaxId = -1;

    return head;
};

/*
    Read Menue Items From Files
    Dependancies :- setItemNode Function,setLength Function
    DataStructure Used :- MenueCategory, MenueItem
 */
void *getMenueItemFromFile(char file[], Storage *head)
{

    // File Headaling Pointers
    int column = 0, row = 0;
    char buffer[1024];
    // FILE *fp = fopen(file, "ra");
    char pre[] = "./Database/";
    FILE *fp = fopen(strcat(pre, file), "ra");

    // if (fp == NULL)
    // {
    //     printf("FIle NOt Open\n");
    // }
    // else
    // {
    //     PrintError("FIle Exiest");
    // }
    MenueCategory *HeadTraker = NULL;
    MenuItem *HeadPointer = NULL;
    MenuItem *trakItem = NULL;

    while (fgets(buffer, 1024, fp))
    {
        HeadTraker = head->Start;
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
                if (head->MaxId < atoi(value))
                {
                    head->MaxId = atoi(value);
                }
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

        // printf("%d\t%d\t%s\t%d\n", HeadPointer->id, HeadPointer->category, HeadPointer->name, HeadPointer->price);
        setItemNode(head->Start, HeadPointer);
        // printf("\n");
    }
    fclose(fp);
};

/*
    Display Menue Item Containing In specific Cetogory
    Dependancies :- None
    DataStructure Used :- MenueItem
*/
void DisplayCetegoryItem(MenuItem *track)
{

    while (track != NULL)
    {

        LogMark();
        printf("| ItemId\t| ItemName\t\t\t\t\t| ItemPrice");
        LogMark();
        while (track != NULL)
        {
            printf("| %d\t\t| %s\t| %d Rs\n", track->id, track->name, track->price);
            track = track->next;
        }
    }
}

/*
    Display Full Menue
    Dependancies :- DisplayCetegoryItem Function
    DataStructure Used :- MenueItem, MenueCategory
*/
void DisplayFullMenue(MenueCategory *start)
{

    MenuItem *track = NULL;
    while (start != NULL)
    {
        // LogMark();
        // printf("\t\t%s", start->category);
        PrintHeading(start->category);
        DisplayCetegoryItem(start->items);
        start = start->next;
    }
}

/*
    Display Only Cetegory Of Menue
    Dependancies :- None
    DataStructure Used :- MenueCategory
*/
void DisplayCetegory(MenueCategory *head)
{

    PrintHeading("Menue Cetegory");
    LogMark();
    printf("| CategoryID\t| CetorogyName");
    LogMark();
    while (head != NULL)
    {
        printf("| %d\t\t| %s\n", head->categoryNumber, head->category);
        head = head->next;
    }
};

/*
    Select Category Froms Menue
    Dependancies :- None
    DataStructure Used :- MenueCategory
*/
MenueCategory *SelectCetegoryById(MenueCategory *start, int id)
{

    while (start != NULL)
    {
        if (start->categoryNumber == id)
        {
            return start;
        }
        start = start->next;
    }
    return NULL;
}

/*
    Select Items Froms Specific Category From Item Id
    Dependancies :- None
    DataStructure Used :- MenuItem, MenueCategory
*/
MenuItem *SelectItemById(MenueCategory *start, int id)
{
    MenuItem *track = start->items;
    while (track != NULL)
    {
        if (track->id == id)
        {
            break;
        }
        track = track->next;
    }
    return track;
}

/*
    Displlay OrderItem Item From Order
    Dependancies :- None
    DataStructure Used :- Order,
*/
void DisplayOrder(Order *order)
{
    OrderItem *node = order->items;
    PrintHeading("My Order");
    printf("| ItemName\t\t\t\t\t| ItemPrice\t| Quantity\t| Total\n");
    while (node != NULL)
    {
        printf("| %s\t| %d\t\t| %d\t\t| %d\n", node->item->name, node->item->price, node->quantity, node->itemTotal);
        node = node->next;
    }
    LogMark();
    printf("Total Item :- %d\n", order->totalItem);
    printf("Fianl Total :- %d", order->total);
    LogMark();
}

/*
    Displlay Order Item From Order
    Dependancies :- DisplayCetegory , DisplayCetegoryItem, SelectCetegoryById, SelectItemById Functions
    DataStructure Used :- Order, MenueCategory, MenuItem
*/
Order *CreateOrder(MenueCategory *start)
{
    int flage = 1;
    MenueCategory *selectCetegory = NULL;
    OrderItem *myOrder = NULL;
    Order *track = NULL;
    MenuItem *orderItem = NULL;
    int Id;

    do
    {
        selectCetegory = NULL;
        orderItem = NULL;

        if (track == NULL)
        {
            track = (Order *)malloc(sizeof(Order));
            track->total = 0;
            track->totalItem = 0;
            track->id = -1;
            myOrder = (OrderItem *)malloc(sizeof(OrderItem));
            track->items = myOrder;
        }
        else
        {
            myOrder->next = (OrderItem *)malloc(sizeof(OrderItem));
            myOrder = myOrder->next;
        }
        myOrder->next = NULL;

        while (selectCetegory == NULL)
        {

            DisplayCetegory(start);
            LogMark();
            printf("What Would you like to Order?\nSelect Cetegory : ");
            scanf("%d", &Id);

            selectCetegory = SelectCetegoryById(start, Id);
            if (selectCetegory == NULL)
            {
                PrintError("Select Id Proprerly\nEnter Only Cetogory ID");
            }
        }

        while (orderItem == NULL)
        {

            DisplayCetegoryItem(selectCetegory->items);
            LogMark();
            printf("Select Item Which you Want to Order :- ");
            scanf("%d", &Id);
            orderItem = SelectItemById(selectCetegory, Id);
            if (orderItem == NULL)
            {
                PrintError("Select Item Properly\nInsert Only Item Id : ");
            }
        }
        myOrder->item = orderItem;

        removeLength(orderItem->name);
        printf("How many %s do you want to Order ?\nEnter Quentity : ", orderItem->name);
        setLength(orderItem->name, 40);
        scanf("%d", &myOrder->quantity);

        myOrder->itemTotal = myOrder->quantity * myOrder->item->price;
        track->total = track->total + myOrder->itemTotal;
        track->totalItem = track->totalItem + myOrder->quantity;

        LogMark();
        printf("Do you want any thing Else ?");
        printf("\n0. No");
        printf("\n1. Yes");
        LogMark();
        printf("\nEnter Your Choice : ");
        scanf("%d", &flage);

    } while (flage == 1);

    return track;
}

void main()
{
    Storage *start = getMenueCategorysFromFile("CategoryType.csv");
    getMenueItemFromFile("MenueItem.csv", start);
    Order *order = CreateOrder(start->Start);
    LogMark();
    printf("Total Items :- %d\nTotal Amount :- %d\n", order->totalItem, order->total);
    DisplayOrder(order);
}
