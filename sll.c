#include <stdio.h>
#include <stdlib.h>

// Define a node structure
struct Node {
    int data;
    struct Node* next;
};

// Function prototypes
void createLinkedList(struct Node** head);
void insertAfterPosition(struct Node** head, int position, int data);
void insertBeforePosition(struct Node** head, int position, int data);
void insertAtEnd(struct Node** head, int data);
void insertAtBeginning(struct Node** head, int data);
void deleteAfterPosition(struct Node** head, int position);
void deleteFromEnd(struct Node** head);
void deleteFromBeginning(struct Node** head);
int searchValue(struct Node* head, int value);
void destroyLinkedList(struct Node** head);
void displayLinkedList(struct Node* head);

int main() {
    struct Node* head = NULL;
    int choice, data, position, result;

    while (1) {
        printf("\n--- Singly Linked List Operations ---\n");
        printf("1. Create a linked list\n");
        printf("2. Insert after a given position\n");
        printf("3. Insert before a given position\n");
        printf("4. Insert at the end\n");
        printf("5. Insert at the beginning\n");
        printf("6. Delete after a given position\n");
        printf("7. Delete from the end\n");
        printf("8. Delete from the beginning\n");
        printf("9. Search for a value\n");
        printf("10. Destroy the linked list\n");
        printf("11. Display the linked list\n");
        printf("12. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createLinkedList(&head);
                break;
            case 2:
                printf("Enter position after which to insert: ");
                scanf("%d", &position);
                printf("Enter data: ");
                scanf("%d", &data);
                insertAfterPosition(&head, position, data);
                break;
            case 3:
                printf("Enter position before which to insert: ");
                scanf("%d", &position);
                printf("Enter data: ");
                scanf("%d", &data);
                insertBeforePosition(&head, position, data);
                break;
            case 4:
                printf("Enter data to insert at end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 5:
                printf("Enter data to insert at beginning: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 6:
                printf("Enter position after which to delete: ");
                scanf("%d", &position);
                deleteAfterPosition(&head, position);
                break;
            case 7:
                deleteFromEnd(&head);
                break;
            case 8:
                deleteFromBeginning(&head);
                break;
            case 9:
                printf("Enter value to search: ");
                scanf("%d", &data);
                result = searchValue(head, data);
                if (result != -1) {
                    printf("Value found at position %d\n", result);
                } else {
                    printf("Value not found in the list\n");
                }
                break;
            case 10:
                destroyLinkedList(&head);
                break;
            case 11:
                displayLinkedList(head);
                break;
            case 12:
                destroyLinkedList(&head);
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

// Create a linked list
void createLinkedList(struct Node** head) {
    int n, data;
    struct Node* newNode;
    struct Node* temp;

    printf("Enter the number of nodes: ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Invalid number of nodes\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        printf("Enter data for node %d: ", i + 1);
        scanf("%d", &data);

        newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = data;
        newNode->next = NULL;

        if (*head == NULL) {
            *head = newNode;
            temp = *head;
        } else {
            temp->next = newNode;
            temp = temp->next;
        }
    }
}

// Insert after a given position
void insertAfterPosition(struct Node** head, int position, int data) {
    struct Node* newNode;
    struct Node* temp = *head;
    int i;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;

    for (i = 0; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    temp->next = newNode;
}

// Insert before a given position
void insertBeforePosition(struct Node** head, int position, int data) {
    struct Node* newNode;
    struct Node* temp = *head;
    struct Node* prev = NULL;
    int i;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;

    for (i = 0; i < position - 1 && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Position out of bounds\n");
        free(newNode);
        return;
    }

    newNode->next = temp;

    if (prev != NULL) {
        prev->next = newNode;
    } else {
        *head = newNode;
    }
}

// Insert at the end
void insertAtEnd(struct Node** head, int data) {
    struct Node* newNode;
    struct Node* temp = *head;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    while (temp->next != NULL) {
        temp = temp->next;
    }

    temp->next = newNode;
}

// Insert at the beginning
void insertAtBeginning(struct Node** head, int data) {
    struct Node* newNode;

    newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = data;
    newNode->next = *head;

    *head = newNode;
}

// Delete after a given position
void deleteAfterPosition(struct Node** head, int position) {
    struct Node* temp = *head;
    struct Node* nodeToDelete;
    int i;

    for (i = 0; i < position && temp != NULL; i++) {
        temp = temp->next;
    }

    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds or no node to delete after the given position\n");
        return;
    }

    nodeToDelete = temp->next;
    temp->next = temp->next->next;
    free(nodeToDelete);
}

// Delete from the end
void deleteFromEnd(struct Node** head) {
    struct Node* temp = *head;
    struct Node* prev = NULL;

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    while (temp->next != NULL) {
        prev = temp;
        temp = temp->next;
    }

    if (prev != NULL) {
        prev->next = NULL;
    } else {
        *head = NULL;
    }

    free(temp);
}

// Delete from the beginning
void deleteFromBeginning(struct Node** head) {
    struct Node* temp;

    if (*head == NULL) {
        printf("List is empty\n");
        return;
    }

    temp = *head;
    *head = (*head)->next;
    free(temp);
}

// Search for a value
int searchValue(struct Node* head, int value) {
    struct Node* temp = head;
    int position = 0;

    while (temp != NULL) {
        if (temp->data == value) {
            return position;
        }
        temp = temp->next;
        position++;
    }

    return -1; // Value not found
}

// Destroy the linked list
void destroyLinkedList(struct Node** head) {
    struct Node* temp;

    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }

    printf("Linked list destroyed\n");
}

// Display the linked list
void displayLinkedList(struct Node* head) {
    struct Node* temp = head;

    if (head == NULL) {
        printf("List is empty\n");
        return;
    }

    printf("Linked list: ");
    while (temp != NULL) {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}