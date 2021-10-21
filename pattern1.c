#include <stdio.h>
#include <conio.h>
/*
 *******
 ******
 *****
 ****
 ***
 **
 *
 */
void main()
{

    int n, i, j;

    printf("Enter Number of Rows :- ");
    scanf("%d", &n);

    printf("\n---------------------------------------------------\n");
    for (i = 0; i < n; i++)
    {
        for (j = i; j < n; j++)
        {
            printf("*");
        }
        printf("\n");
    }
    printf("---------------------------------------------------");
}