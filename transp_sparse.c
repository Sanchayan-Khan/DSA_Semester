#include <stdio.h>
#include <stdlib.h>
int main() 
{
    int mt[100][3], tr[100][3];
    int m, n, i, j, k = 1, a;
    printf("Enter the number of rows and columns: \n");
    scanf("%d%d", &m, &n);
    mt[0][0] = m;
    mt[0][1] = n;
    printf("\nEnter the numbers:\n");
    for (i = 0; i < m; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            scanf("%d", &a);
            if (a != 0) 
            {
                mt[k][0] = i;
                mt[k][1] = j;
                mt[k++][2] = a;
            }
        }
    }
    mt[0][2] = k - 1;
    k = 1;
    printf("\nOriginal Matrix:\n");
    for (i = 0; i < m; i++) 
    {
        for (j = 0; j < n; j++) 
        {
            if (mt[k][0] == i && mt[k][1] == j)
                printf("%d\t", mt[k++][2]);
            else
                printf("0\t");
        }
        printf("\n");
    }
    printf("\nSparse representation: \n");
    for (i = 0; i <= mt[0][2]; i++) 
    {
        printf("%d\t%d\t%d\n", mt[i][0], mt[i][1], mt[i][2]);
    }
    tr[0][0] = n;
    tr[0][1] = m;
    tr[0][2] = mt[0][2];
    k = 1;
    for (i = 1; i <= mt[0][2]; i++) 
    {
        tr[k][0] = mt[i][1];
        tr[k][1] = mt[i][0];
        tr[k][2] = mt[i][2];
        k++;
    }
    printf("\nTranspose Matrix:\n");
    k = 1;
    for (i = 0; i < tr[0][0]; i++) 
    {
        for (j = 0; j < tr[0][1]; j++) 
        {
            if (tr[k][0] == i && tr[k][1] == j)
                printf("%d\t", tr[k++][2]);
            else
                printf("0\t");
        }
        printf("\n");
    }
    printf("\nTranspose Sparse representation: \n");
    for (i = 0; i <= tr[0][2]; i++) 
    {
        printf("%d\t%d\t%d\n", tr[i][0], tr[i][1], tr[i][2]);
    }
    return 0;
}