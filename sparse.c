#include<stdio.h>
#include<stdlib.h>
int main()
{
    int mt[100][3];
    int m,n,i=0,j=0,k=1,a;
    printf("Enter the no. of rows and columns: \n");
    scanf("%d%d",&m,&n);
    mt[0][0]=m;
    mt[0][1]=n;
    printf("\nEnter the numbers:");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&a);
            if(a!=0)
            {
                mt[k][0]=i;
                mt[k][1]=j;
                mt[k++][2]=a;
            }
        }
    }
    mt[0][2]=k-1;
    k=1;
    printf("\nOriginal Matrix:\n");
    for(i=0;i<m;i++)
    {
        for(j=0;j<n;j++)
        {
            if(mt[k][0]==i && mt[k][1]==j)
            printf("%d\t",mt[k++][2]);
            else
            printf("0\t");
        }
        printf("\n");
    }
    printf("\nSparse representation: \n");
    for(i=0;i<k;i++)
    {
        printf("%d\t%d\t%d",mt[i][0],mt[i][1],mt[i][2]);
        printf("\n");
    }
    return 0;
}