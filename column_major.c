#include <stdio.h>
#include <stdlib.h>
int i,j;
void transpose(int **mat, int **trans, int m, int n) 
{
    for (i = 0; i < n; i++) 
    {
        for (j = 0; j < m; j++) 
        {
            trans[i][j] = mat[j][i];
        }
    }
}
void printmatrix(int **p,int a,int b)
{
    
    for(i=0;i<a;i++)
    {
        for(j=0;j<b;j++)
        printf("%d\t",p[i][j]);
        printf("\n");
    }
}
int main() 
{
    int m, n;
    printf("Enter the number of rows: ");
    scanf("%d", &m);
    printf("Enter the number of columns: ");
    scanf("%d", &n);
    int **mat = (int **)malloc(m * sizeof(int *));
    for (int i = 0; i < m; i++) 
    {
        mat[i] = (int *)malloc(n * sizeof(int));
    }
    printf("Enter the matrix elements:\n");
    for (int i = 0; i < m; i++) 
    {
        for (int j = 0; j < n; j++) 
        {
            scanf("%d", &mat[i][j]);
        }
    }
    int **trans = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) 
    {
        trans[i] = (int *)malloc(m * sizeof(int));
    }
    transpose(mat, trans, m, n);
    printf("\nOriginal Matrix: \n");
    printmatrix(mat,m,n);
    printf("\nTranspose Matrix:\n");
    printmatrix(trans,n,m);
    printf("Enter row and column indices (starting from 0): ");
    scanf("%d %d", &i, &j);
    int row_major_index_original = i * n + j;
    int col_major_index_transposed = i * m + j;
    printf("Element at (%d, %d) using row-major in original matrix: %d\n", i, j, mat[i][j]);
    printf("Element at (%d, %d) using column-major in transposed matrix: %d\n",j, i, trans[j][i]);
    for (int i = 0; i < m; i++) 
    {
        free(mat[i]);
    }
    free(mat);
    for (int i = 0; i < n; i++) 
    {
        free(trans[i]);
    }
    free(trans);
    return 0;
}