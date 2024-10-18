#include <stdio.h>
#include <stdlib.h>

// Structure for a node in the binary search tree
typedef struct Node {
    int data;
    struct Node *left, *right;
} Node;

// Stack structure for non-recursive postorder traversal
typedef struct Stack {
    Node *arr[1000];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, Node *n) {
    s->arr[++s->top] = n;
}

Node* pop(Stack *s) {
    if (isEmpty(s)) return NULL;
    return s->arr[s->top--];
}

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->left = newNode->right = NULL;
    return newNode;
}

// Function to insert a node in BST
Node* insertNode(Node* root, int data) {
    if (root == NULL) return createNode(data);
    if (data < root->data)
        root->left = insertNode(root->left, data);
    else if (data > root->data)
        root->right = insertNode(root->right, data);
    return root;
}

// Function to search for a value and count nodes traversed
int searchValue(Node* root, int key, int* count) {
    if (root == NULL) return 0;
    (*count)++;
    if (root->data == key) return 1;
    if (key < root->data)
        return searchValue(root->left, key, count);
    else
        return searchValue(root->right, key, count);
}

// Function to find the minimum value node in BST (for deletion)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Function to delete a node in BST
Node* deleteNode(Node* root, int key) {
    if (root == NULL) return root;
    if (key < root->data)
        root->left = deleteNode(root->left, key);
    else if (key > root->data)
        root->right = deleteNode(root->right, key);
    else {
        if (root->left == NULL) {
            Node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            Node* temp = root->left;
            free(root);
            return temp;
        }
        Node* temp = minValueNode(root->right);
        root->data = temp->data;
        root->right = deleteNode(root->right, temp->data);
    }
    return root;
}

// Function to find and print values in a range [low, high]
void rangeQuery(Node* root, int low, int high) {
    if (root == NULL) return;
    if (low < root->data)
        rangeQuery(root->left, low, high);
    if (low <= root->data && high >= root->data)
        printf("%d ", root->data);
    if (high > root->data)
        rangeQuery(root->right, low, high);
}

// Function to calculate height of the BST
int height(Node* node) {
    if (node == NULL) return 0;
    int leftHeight = height(node->left);
    int rightHeight = height(node->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Non-recursive post-order traversal using one stack
void postOrderTraversal(Node* root) {
    if (root == NULL) return;
    Stack s;
    initStack(&s);
    Node* lastVisited = NULL;
    Node* current = root;
    
    while (!isEmpty(&s) || current != NULL) {
        if (current != NULL) {
            push(&s, current);
            current = current->left;
        } else {
            Node* peekNode = s.arr[s.top];
            if (peekNode->right != NULL && lastVisited != peekNode->right) {
                current = peekNode->right;
            } else {
                printf("%d ", peekNode->data);
                lastVisited = pop(&s);
            }
        }
    }
}

// Function to calculate subtree sum
int subtreeSum(Node* root) {
    if (root == NULL) return 0;
    return root->data + subtreeSum(root->left) + subtreeSum(root->right);
}

// Function to insert subtree sums into a new BST
Node* insertSubtreeSums(Node* root, Node* newBST) {
    if (root == NULL) return newBST;
    int sum = subtreeSum(root);
    newBST = insertNode(newBST, sum);
    newBST = insertSubtreeSums(root->left, newBST);
    newBST = insertSubtreeSums(root->right, newBST);
    return newBST;
}

// Function to delete nodes in a range [low, high]
Node* deleteRange(Node* root, int low, int high) {
    if (root == NULL) return root;
    root->left = deleteRange(root->left, low, high);
    root->right = deleteRange(root->right, low, high);
    if (root->data >= low && root->data <= high)
        root = deleteNode(root, root->data);
    return root;
}

// Main function to implement switch case
int main() {
    Node* root = NULL;
    Node* newBST = NULL;
    int choice, value, count, low, high;

    // Assuming input file is already created with 1000 random integers
    FILE* file = fopen("random_numbers.txt", "r");
    if (!file) {
        printf("File not found!\n");
        return 1;
    }

    // Reading from the file and inserting into the BST
    for (int i = 0; i < 1000; i++) {
        fscanf(file, "%d", &value);
        root = insertNode(root, value);
    }
    fclose(file);

    do {
        printf("\nMenu:\n");
        printf("1. Search for a value\n");
        printf("2. Delete a value\n");
        printf("3. Range Query\n");
        printf("4. Calculate Height of Subtrees\n");
        printf("5. PostOrder Traversal (Non-Recursive)\n");
        printf("6. Delete nodes in a range\n");
        printf("7. Insert Subtree Sums into a New BST\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter value to search: ");
                scanf("%d", &value);
                count = 0;
                if (searchValue(root, value, &count))
                    printf("Value found! Nodes traversed: %d\n", count);
                else
                    printf("Value not found!\n");
                break;

            case 2:
                printf("Enter value to delete: ");
                scanf("%d", &value);
                root = deleteNode(root, value);
                printf("Value deleted if present.\n");
                break;

            case 3:
                printf("Enter lower bound: ");
                scanf("%d", &low);
                printf("Enter upper bound: ");
                scanf("%d", &high);
                printf("Values in the range [%d, %d]: ", low, high);
                rangeQuery(root, low, high);
                printf("\n");
                break;

            case 4:
                printf("Enter node value to find subtree heights: ");
                scanf("%d", &value);
                count = 0;
                if (searchValue(root, value, &count)) {
                    Node* temp = root;
                    while (temp && temp->data != value) {
                        if (value < temp->data)
                            temp = temp->left;
                        else
                            temp = temp->right;
                    }
                    if (temp) {
                        printf("Left subtree height: %d\n", height(temp->left));
                        printf("Right subtree height: %d\n", height(temp->right));
                    }
                } else {
                    printf("Node not found!\n");
                }
                break;

            case 5:
                printf("PostOrder traversal (non-recursive): ");
                postOrderTraversal(root);
                printf("\n");
                break;

            case 6:
                printf("Enter lower bound for deletion: ");
                scanf("%d", &low);
                printf("Enter upper bound for deletion: ");
                scanf("%d", &high);
                root = deleteRange(root, low, high);
                printf("Nodes in the range deleted.\n");
                break;

            case 7:
                newBST = insertSubtreeSums(root, newBST);
                printf("Subtree sums inserted into new BST.\n");
                break;

            case 8:
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice!\n");
        }
    } while (choice != 8);

    return 0;
}