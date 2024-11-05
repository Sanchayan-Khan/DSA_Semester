#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// Define a binomial heap node structure
typedef struct BinomialNode {
    int key;
    int degree;
    struct BinomialNode* parent;
    struct BinomialNode* child;
    struct BinomialNode* sibling;
} BinomialNode;

// Create a new binomial heap node
BinomialNode* createNode(int key) {
    BinomialNode* newNode = (BinomialNode*)malloc(sizeof(BinomialNode));
    if (!newNode) {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE);
    }
    newNode->key = key;
    newNode->degree = 0;
    newNode->parent = newNode->child = newNode->sibling = NULL;
    return newNode;
}

// Link two binomial trees of the same degree
BinomialNode* linkTrees(BinomialNode* b1, BinomialNode* b2) {
    if (!b1 || !b2) return NULL;
    if (b1->key > b2->key) {
        BinomialNode* temp = b1;
        b1 = b2;
        b2 = temp;
    }
    b2->parent = b1;
    b2->sibling = b1->child;
    b1->child = b2;
    b1->degree++;
    return b1;
}

// Merge two binomial heaps
BinomialNode* mergeHeaps(BinomialNode* h1, BinomialNode* h2) {
    if (!h1) return h2;
    if (!h2) return h1;
    BinomialNode* head = NULL;
    BinomialNode** pos = &head;
    while (h1 && h2) {
        if (h1->degree <= h2->degree) {
            *pos = h1;
            h1 = h1->sibling;
        } else {
            *pos = h2;
            h2 = h2->sibling;
        }
        pos = &(*pos)->sibling;
    }
    *pos = h1 ? h1 : h2;
    return head;
}

// Union of two binomial heaps
BinomialNode* unionHeaps(BinomialNode* h1, BinomialNode* h2) {
    if (!h1 && !h2) return NULL;
    BinomialNode* mergedHeap = mergeHeaps(h1, h2);
    if (!mergedHeap) return NULL;
    BinomialNode* prev = NULL;
    BinomialNode* curr = mergedHeap;
    BinomialNode* next = curr->sibling;
    while (next) {
        if (curr->degree != next->degree ||
            (next->sibling && next->sibling->degree == curr->degree)) {
            prev = curr;
            curr = next;
        } else if (curr->key <= next->key) {
            curr->sibling = next->sibling;
            curr = linkTrees(curr, next);
        } else {
            if (!prev) {
                mergedHeap = next;
            } else {
                prev->sibling = next;
            }
            curr = linkTrees(next, curr);
        }
        next = curr->sibling;
    }
    return mergedHeap;
}

// Insert a node into the binomial heap
BinomialNode* insertNode(BinomialNode* heap, int key) {
    BinomialNode* newNode = createNode(key);
    return unionHeaps(heap, newNode);
}

// Find the minimum node in a binomial heap
BinomialNode* findMinNode(BinomialNode* heap) {
    if (!heap) {
        printf("Heap is empty.\n");
        return NULL;
    }
    BinomialNode* minNode = NULL;
    BinomialNode* curr = heap;
    int min = INT_MAX;
    while (curr) {
        if (curr->key < min) {
            min = curr->key;
            minNode = curr;
        }
        curr = curr->sibling;
    }
    return minNode;
}

// Extract the minimum node from a binomial heap
BinomialNode* extractMin(BinomialNode* heap) {
    if (!heap) {
        printf("Heap is empty.\n");
        return NULL;
    }
    BinomialNode* minNode = findMinNode(heap);
    BinomialNode* prev = NULL;
    BinomialNode* curr = heap;

    // Locate minNode and unlink it
    while (curr && curr != minNode) {
        prev = curr;
        curr = curr->sibling;
    }
    if (prev) prev->sibling = minNode->sibling;
    else heap = minNode->sibling;

    // Reverse the child list of minNode
    BinomialNode* child = minNode->child;
    BinomialNode* prevChild = NULL;
    while (child) {
        BinomialNode* next = child->sibling;
        child->sibling = prevChild;
        prevChild = child;
        child = next;
    }
    free(minNode);
    return unionHeaps(heap, prevChild);
}

// Print a binomial heap
void printHeap(BinomialNode* heap) {
    if (!heap) {
        printf("Heap is empty.\n");
        return;
    }
    printf("Heap structure:\n");
    while (heap) {
        printf("Degree %d, Key %d ", heap->degree, heap->key);
        if (heap->child) {
            printf("(children: ");
            printHeap(heap->child);
            printf(") ");
        }
        heap = heap->sibling;
        printf("\n");
    }
}

// Main function with menu
int main() {
    BinomialNode* heap = NULL;
    int choice, key;
    do {
        printf("\n--- Binomial Heap Menu ---\n");
        printf("1. Insert\n");
        printf("2. Find Minimum\n");
        printf("3. Extract Minimum\n");
        printf("4. Print Heap\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {  // Check for valid input
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice) {
            case 1:
                printf("Enter the key to insert: ");
                if (scanf("%d", &key) != 1) {
                    printf("Invalid key. Returning to menu.\n");
                    break;
                }
                heap = insertNode(heap, key);
                printf("Key %d inserted.\n", key);
                break;
            case 2: {
                BinomialNode* minNode = findMinNode(heap);
                if (minNode) {
                    printf("Minimum key: %d\n", minNode->key);
                }
                break;
            }
            case 3:
                heap = extractMin(heap);
                printf("Minimum key extracted.\n");
                break;
            case 4:
                printHeap(heap);
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 5);
    return 0;
}