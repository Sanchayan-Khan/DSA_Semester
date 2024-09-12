#include <stdio.h>
#include <stdlib.h>
struct Element 
{
    int row;
    int col;
    int value;
};
struct SparseMatrix 
{
    int rows;
    int cols;
    int numele;
    struct Element *ele;
};
void createMatrix(struct SparseMatrix *mat) 
{
    printf("Enter rows and columns: ");
    scanf("%d %d", &mat->rows, &mat->cols);
    printf("Enter number of non-zero elements: ");
    scanf("%d", &mat->numele);
    mat->ele = (struct Element *)malloc(mat->numele * sizeof(struct Element));
    printf("Enter row, column, and value for each non-zero element:\n");
    for (int i = 0; i < mat->numele; i++) 
    {
        scanf("%d %d %d", &mat->ele[i].row, &mat->ele[i].col, &mat->ele[i].value);
    }
}

void displayMatrix(struct SparseMatrix mat) 
{
    for (int i = 0; i < mat.numele; i++) 
    {
        printf("%d\t%d\t%d\n", mat.ele[i].row, mat.ele[i].col, mat.ele[i].value);
    }
}

struct SparseMatrix addMatrices(struct SparseMatrix A, struct SparseMatrix B) 
{
    if (A.rows != B.rows || A.cols != B.cols) 
    {
        printf("Matrices cannot be added.\n");
        exit(1);
    }
    struct SparseMatrix C;
    C.rows = A.rows;
    C.cols = A.cols;
    C.numele = 0;
    C.ele = (struct Element *)malloc((A.numele + B.numele) * sizeof(struct Element));  // Allocate memory for the sum matrix
    int i = 0, j = 0, k = 0;
    while (i < A.numele && j < B.numele) 
    {
        if (A.ele[i].row < B.ele[j].row || (A.ele[i].row == B.ele[j].row && A.ele[i].col < B.ele[j].col)) 
        {
            C.ele[k++] = A.ele[i++];
        } 
        else if (A.ele[i].row > B.ele[j].row || (A.ele[i].row == B.ele[j].row && A.ele[i].col > B.ele[j].col)) 
        {
            C.ele[k++] = B.ele[j++];
        } 
        else 
        { // elements have the same row and column
            C.ele[k].row = A.ele[i].row;
            C.ele[k].col = A.ele[i].col;
            C.ele[k].value = A.ele[i].value + B.ele[j].value;
            i++;
            j++;
            k++;
        }
    }
    while (i < A.numele) 
    {
        C.ele[k++] = A.ele[i++];
    }

    while (j < B.numele) 
    {
        C.ele[k++] = B.ele[j++];
    }

    C.numele = k;  // Update the number of non-zero elements in C
    return C;
}
int main() 
{
    struct SparseMatrix A, B, C;
    printf("Enter first matrix:\n");
    createMatrix(&A);

    printf("Enter second matrix:\n");
    createMatrix(&B);

    C = addMatrices(A, B);

    printf("Matrix A:\n");
    displayMatrix(A);

    printf("Matrix B:\n");
    displayMatrix(B);

    printf("Matrix C (Sum):\n");
    displayMatrix(C);

    // Free allocated memory
    free(A.ele);
    free(B.ele);
    free(C.ele);

    return 0;
}