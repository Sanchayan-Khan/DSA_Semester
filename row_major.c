#include<stdio.h>
#include<stdlib.h>
int i,j;
void printmatrix(int **p,int a,int b)
{
    
    for(i=0;i<a;i++)
    {
        for(j=0;j<b;j++)
        printf("%d\t",p[i][j]);
        printf("\n");
    }
}
void insert(int **p,int m,int n)
{
    printf("\nEnter the values:\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        scanf("%d",&p[i][j]);
    }
}
int main()
{
    int m,n,a,b;
    printf("Enter the no. of rows and columns of the matrix: ");
    scanf("%d%d",&m,&n);
    int **mat=(int **)malloc(sizeof(int *)*m);
    int *m1=(int*)malloc(sizeof(int)*m*n);
    int i,j,k=0;
    for(i=0;i<m;i++)
    {
        mat[i]=(int*)malloc(sizeof(int)*n);
    }
    insert(mat,m,n);
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        m1[k++]=mat[i][j];
    }
    k=0;
    printf("\nOriginal Matrix: \n");
    printmatrix(mat,m,n);
    printf("\nEnter the index of the value for which row major formula will be verified:");
    scanf("%d%d",&a,&b);
    while(a>m || b>n)
    {
        printf("\nWrong Input!Enter again");
        scanf("%d%d",&a,&b);
    }
    k=(a*n)+b;
    printf("Element at (%d, %d) in 2D array: %d\n",a,b,mat[a][b]);
    printf("Element at index %d in 1D array: %d\n", k, m1[k]);
    free(mat);
    free(m1);
    return 0;
}