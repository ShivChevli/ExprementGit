#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

typedef struct USER
{
    int type;
    int id;
    int status;
    char userName[20];
    char password[20];
    char email[40];
    char moNumber[10];
    struct USER *next;
} User;
typedef struct USERHEAD
{
    // int id;
    int NumberOfUser;
    int AdminUser;
    int NormalUser;
    struct USER *next;
} UserHeadNode;

void PrintHeading(char str[])
{
    printf("\n===========================================================\n");
    printf("\t\t%s \n", str);
    printf("===========================================================\n");
};

void PrintError(char str[])
{
    printf("\n------------------------:  Error  :------------------------\n");
    printf("\t\t%s", str);
    printf("\n-----------------------------------------------------------\n");
}

void LogMark()
{
    printf("\n\n-----------------------------------------------------------\n");
};

void DiaplayUser(UserHeadNode *head)
{
    User *pt = head->next;
    printf("\n------------------------------------------------------------------------------------------------------------------------------------\n");
    printf("| UserId\t| UserType\t| UserStatus\t| UserName\t| Email\t\t\t\t| MobileNumber\t| UserPassword\t\n");
    printf("---------------------------------------------------------------------------------------------------------------------------------------\n");
    while (pt != NULL)
    {
        printf("| %d\t\t| %d\t\t| %d\t\t| %s\t\t| %s\t\t| %s\t| %s\n", pt->id, pt->type, pt->status, pt->userName, pt->email, pt->moNumber, pt->password);
        pt = pt->next;
    }
    printf("\nTotal User :- %d", head->NumberOfUser);
    printf("\nAdmin User :- %d", head->AdminUser);
    printf("\nNormal User :- %d\n", head->NormalUser);
};

User *UserValidation(User *u1)
{
    char temp[20], pwd[20];
    int type, i, try = 3;

    PrintHeading("User Type");
    printf("0. User\n");
    printf("1. Admin\n");

    printf("Enter User type :- ");
    scanf("%d", &type);

    LogMark();
    printf("Enter User Name :- ");
    scanf("%s", temp);

    User *ans = NULL;

    while (u1 != NULL)
    {
        if (u1->type == type)
        {
            if (strcmp(u1->userName, temp) == 0)
            {
                while (try != 0)
                {
                    printf("Enter Password :- ");
                    scanf("%s", pwd);
                    if (strcmp(u1->password, pwd) == 0)
                    {
                        ans = u1;
                        try = 0;
                    }
                    else
                    {
                        printf("Enter Correct String\n");
                        try--;
                    }
                };
                if (try == 0)
                    break;
            }
            else
            {
                u1 = u1->next;
            }
        }
        else
        {
            u1 = u1->next;
        }
    }
    return ans;
}

User *createUser(User *pt)
{
    char p1[20], p2[20], tempUser[20], tempEmail[40], tempNumber[15];
    User *temp = NULL;
    printf("Enter User Name :- ");
    scanf("%s", tempUser);
    printf("Enter Email Address :- ");
    scanf("%s", tempEmail);
    printf("Enter Mobile Number :- ");
    scanf("%s", tempNumber);

    printf("Enter Password :- ");
    scanf("%s", p1);
    printf("Re-enter Password :- ");
    scanf("%s", p2);
    if (strcmp(p1, p2) == 0)
    {
        temp = (User *)malloc(sizeof(User));
        strcpy(temp->userName, tempUser);
        strcpy(temp->password, p1);
        strcpy(temp->email, tempEmail);
        strcpy(temp->moNumber, tempNumber);
        temp->type = 0;
        temp->status = 1;
        temp->next = NULL;
    }
    else
    {
        printf("Enter Passwod Correctly\nTry Again");
    }

    return temp;
};

UserHeadNode *getUserFromFile(char file[])
{

    // File Headaling Pointers
    int column = 0, row = 0;
    char buffer[1024];
    char pre[] = "./Database/";
    FILE *fp = fopen(strcat(pre, file), "ra");

    UserHeadNode *head = (UserHeadNode *)malloc(sizeof(UserHeadNode));
    User *HeadPointer = (User *)malloc(sizeof(User));
    head->next = NULL;
    head->AdminUser = 0;
    head->NormalUser = 0;
    head->NumberOfUser = 0;
    User *trak = NULL;

    while (fgets(buffer, 1024, fp))
    {
        row++;
        if (row == 1)
        {
            continue;
        }

        char *value = strtok(buffer, ", ");

        if (head->next == NULL)
        {
            head->next = HeadPointer;
        }
        else
        {
            HeadPointer->next = (User *)malloc(sizeof(User));
            HeadPointer = HeadPointer->next;
        }
        head->NumberOfUser++;
        HeadPointer->next = NULL;
        column = 0;
        while (value)
        {
            value[strcspn(value, "\n")] = '\0';
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
                if (atoi(value) == 1)
                {
                    head->AdminUser++;
                }
                else
                {
                    head->NormalUser++;
                }
                HeadPointer->type = atoi(value);
            }

            // Column 3
            if (column == 2)
            {
                HeadPointer->status = atoi(value);
                // printf("\t\tUser Name :");
            }

            // Column 4
            if (column == 3)
            {
                strcpy(HeadPointer->userName, value);
                // printf("\t\tUser Name :");
            }

            if (column == 4)
            {
                strcpy(HeadPointer->password, value);
                // printf("\t\tUser Password :");
            }

            if (column == 5)
            {
                strcpy(HeadPointer->email, value);
            }

            if (column == 6)
            {
                strcpy(HeadPointer->moNumber, value);
            }

            // printf("%s", value);
            value = strtok(NULL, ", ");
            column++;
        }

        // printf("\n");
    }
    fclose(fp);

    return head;
};

void writeUserTofile(char *file, UserHeadNode *node)
{
    int column = 0, row = 0;
    char buffer[1024];

    char pre[] = "./Database/";
    FILE *fp = fopen(strcat(pre, file), "w");

    fprintf(fp, "UserId,UserType,UserStatus,UserName,UserPassword,EmailAddress,MobileNumber\n");

    User *pt = node->next;
    while (pt != NULL)
    {
        fprintf(fp, "%d,%d,%d,%s,%s,%s,%s\n", pt->id, pt->type, pt->status, pt->userName, pt->password, pt->email, pt->moNumber);
        pt = pt->next;
    }
    fclose(fp);
};

void deleteUser(UserHeadNode *head)
{
    char temp[20], pwd[20];
    int id, i, try = 3;

    DiaplayUser(head);

    printf("\nEnter User Id :- ");
    scanf("%d", &id);

    User *pt = head->next;

    if (pt == NULL)
    {
        PrintError("There is no Valid User");
    }
    else
    {

        while (pt != NULL)
        {
            if (pt->id == id)
            {
                pt->status = 0;
                break;
            }
            pt = pt->next;
        }
    }
}

void main()
{
    int choice;
    UserHeadNode *head = getUserFromFile("FileUser.csv");

    if (head->next == NULL)
    {
        PrintHeading("Cereate New User");
        User *node = createUser(head->next);
        if (node == NULL)
        {
            PrintHeading("User Is Not Created Try Again\n");
        }
        else
        {
            head->next = node;
            node->type = 1;
            head->NumberOfUser++;
            node->id = head->NumberOfUser;
            head->AdminUser++;
        }
    }
    else
    {
        /*
            User LogedIn Functions
         */
        User *flage = UserValidation(head->next);
        if (flage != NULL)
        {
            printf("User Loged IN\n");
            printf(" %s : %s : %s", flage->type == 1 ? "Admin" : "Normal User", flage->userName, flage->password);
        }
        else
        {
            printf("User Does Not Exiest\n");
            exit(0);
        }
    }

    do
    {
        PrintHeading("Menue");
        printf("1. Display User List\n");
        printf("2. Create New User\n");
        printf("3. Delete User\n");
        printf("4. Exit Program\n");
        LogMark();
        printf("Enter Choice :- ");
        scanf("%d", &choice);
        switch (choice)
        {
        case 1:
            PrintHeading("User List");
            DiaplayUser(head);
            break;

        case 2:
            /*
               Add User Functions
            */
            PrintHeading("Cereate New User");
            User *node = createUser(head->next);
            if (node == NULL)
            {
                PrintHeading("User Is Not Created Try Again\n");
            }
            else
            {
                User *temp = head->next;
                while (temp->next != NULL)
                {
                    temp = temp->next;
                }
                temp->next = node;
                temp = temp->next;
                head->NumberOfUser++;
                temp->id = head->NumberOfUser;
                head->NormalUser++;
            }
            break;

        case 3:
            /*
            --------------------------------------------------------
                            Delete User
            --------------------------------------------------------
            */
            PrintHeading("Delete User");
            deleteUser(head);
            break;

        case 4:
            break;
        default:
            PrintError("Enter Valid Choice");
            break;
        }
    } while (choice != 4);

    /*
    --------------------------------------------------------
                    Write User to file
    --------------------------------------------------------
    */
    writeUserTofile("FileUser.csv", head);

    LogMark();
    printf("Thank  you\n");
}