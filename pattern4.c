#include <stdio.h>
#include <conio.h>

void main()
{
    int i, j, k, l, n;

    printf("Enter Number of Rows :- ");
    scanf("%d", &n);

    for (i = 0; i < n; i++)
    {
        for (k = i; k < n; k++)
        {
            printf("  #");
        }
        for (j = 0; j < i; j++)
        {
            printf("  ");
        }
        for (l = 0; l < i; l++)
        {
            printf("    ");
        }
        for (k = i; k < n; k++)
        {
            printf("  #");
        }
        printf("\n");
    }
    for (i = 0; i < n; i++)
    {

        for (j = 0; j <= i; j++)
        {
            printf("  #");
        }
        for (k = i; k < n - 1; k++)
        {
            printf("   ");
        }
        for (l = i; l < n - 1; l++)
        {
            printf("   ");
        }
        for (j = 0; j <= i; j++)
        {
            printf("  #");
        }
        printf("\n");
    }
}