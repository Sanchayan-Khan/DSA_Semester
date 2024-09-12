#include <stdio.h>
#include <stdlib.h>

typedef struct Polynomial
{
    int val;
    int exp;
} Poly;

void insert(Poly p[], int a) 
{
    printf("\nEnter the terms of the polynomial (value and exponent): ");
    for (int i = 0; i < a; i++) 
    {
        scanf("%d %d", &p[i].val, &p[i].exp);
    }
}
void printPolynomial(Poly *p, int n) 
{
    int first_term = 1;
    for (int i = 0; i < n; i++) 
    {
        if (p[i].val != 0) 
        {
            if (first_term) 
            {
                first_term = 0;
            } 
            else 
            {
                printf("+");
            }
            printf("%dx^%d", p[i].val, p[i].exp);
        }
    }
    if (first_term) 
    {
        printf("0");
    }
    printf("\n");
}
int main() 
{
    int a, b;
    printf("\nEnter the no.of terms in first polynomial: ");
    scanf("%d", &a);
    printf("\nEnter the no. of terms in second polynomial: ");
    scanf("%d", &b);
    Poly *p1 = (Poly *)malloc(a * sizeof(Poly));
    Poly *p2 = (Poly *)malloc(b * sizeof(Poly));
    insert(p1, a);
    insert(p2, b);
    int i = 0, j = 0, k = 0;
    Poly *p3 = (Poly *)malloc((a + b) * sizeof(Poly));
    while (i < a && j < b) 
    {
        if (p1[i].exp == p2[j].exp) 
        {
            p3[k].exp = p1[i].exp;
            p3[k].val = p1[i].val + p2[j].val;
            i++;
            j++;
            k++;
        } 
        else if (p1[i].exp < p2[j].exp) 
        {
            p3[k] = p1[i];
            i++;
            k++;
        } 
        else 
        {
            p3[k] = p2[j];
            j++;
            k++;
        }
    }
    while (i < a) 
    {
        p3[k] = p1[i];
        i++;
        k++;
    }
    while (j < b) 
    {
        p3[k] = p2[j];
        j++;
        k++;
    }
    printPolynomial(p3, k); // k is the actual size of p3
    free(p1);
    free(p2);
    free(p3);
    return 0;
}
