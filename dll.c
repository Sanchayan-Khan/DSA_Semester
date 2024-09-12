#include <stdio.h>
#include <stdlib.h>

// Structure to represent a node in the doubly linked list
typedef struct Node {
    int data;
    struct Node* next;
    struct Node* prev;
} Node;

// Function to create a new node
Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}

// Function to create a doubly linked list
Node* createLinkedList() {
    return NULL;
}

// Function to insert at the beginning
void insertAtBeginning(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        newNode->next = *head;
        (*head)->prev = newNode;
        *head = newNode;
    }
}

// Function to insert at the end
void insertAtEnd(Node** head, int data) {
    Node* newNode = createNode(data);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node* temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->prev = temp;
    }
}

// Function to insert after a given position
void insertAfterPosition(Node* head, int position, int data) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    Node* temp = head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// Function to insert before a given position
void insertBeforePosition(Node** head, int position, int data) {
    if (*head == NULL || position == 1) {
        insertAtBeginning(head, data);
        return;
    }
    Node* temp = *head;
    for (int i = 0; i < position - 2 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position out of bounds.\n");
        return;
    }
    Node* newNode = createNode(data);
    newNode->next = temp->next;
    newNode->prev = temp;
    if (temp->next != NULL) {
        temp->next->prev = newNode;
    }
    temp->next = newNode;
}

// Function to delete from the beginning
void deleteFromBeginning(Node** head) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    Node* temp = *head;
    *head = (*head)->next;
    if (*head != NULL) {
        (*head)->prev = NULL;
    }
    free(temp);
}

// Function to delete from the end
void deleteFromEnd(Node** head) {
    if (*head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    Node* temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if (temp->prev != NULL) {
        temp->prev->next = NULL;
    } else {
        *head = NULL;
    }
    free(temp);
}

// Function to delete after a given position
void deleteAfterPosition(Node* head, int position) {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }
    Node* temp = head;
    for (int i = 0; i < position - 1 && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL || temp->next == NULL) {
        printf("Position out of bounds or no node to delete.\n");
        return;
    }
    Node* toDelete = temp->next;
    temp->next = toDelete->next;
    if (toDelete->next != NULL) {
        toDelete->next->prev = temp;
    }
    free(toDelete);
}

// Function to search for a value
Node* search(Node* head, int data) {
    Node* temp = head;
    while (temp != NULL) {
        if (temp->data == data) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

// Function to destroy the doubly linked list
void destroyDLL(Node** head) {
    Node* temp = *head;
    while (temp != NULL) {
        Node* next = temp->next;
        free(temp);
        temp = next;
    }
    *head = NULL;
}

// Function to display the doubly linked list
void displayDLL(Node* head) {
    Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// Main function to test the operations
int main() {
    Node* head = createLinkedList();
    int choice, data, position;

    while (1) {
        printf("\nDoubly Linked List Operations:\n");
        printf("1. Insert at the beginning\n");
        printf("2. Insert at the end\n");
        printf("3. Insert after a given position\n");
        printf("4. Insert before a given position\n");
        printf("5. Delete from the beginning\n");
        printf("6. Delete from the end\n");
        printf("7. Delete after a given position\n");
        printf("8. Search for a value\n");
        printf("9. Display the list\n");
        printf("10. Destroy the list\n");
        printf("11. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter data to insert at the beginning: ");
                scanf("%d", &data);
                insertAtBeginning(&head, data);
                break;
            case 2:
                printf("Enter data to insert at the end: ");
                scanf("%d", &data);
                insertAtEnd(&head, data);
                break;
            case 3:
                printf("Enter position after which to insert: ");
                scanf("%d", &position);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertAfterPosition(head, position, data);
                break;
            case 4:
                printf("Enter position before which to insert: ");
                scanf("%d", &position);
                printf("Enter data to insert: ");
                scanf("%d", &data);
                insertBeforePosition(&head, position, data);
                break;
            case 5:
                deleteFromBeginning(&head);
                break;
            case 6:
                deleteFromEnd(&head);
                break;
            case 7:
                printf("Enter position after which to delete: ");
                scanf("%d", &position);
                deleteAfterPosition(head, position);
                break;
            case 8:
                printf("Enter data to search: ");
                scanf("%d", &data);
                Node* foundNode = search(head, data);
                if (foundNode != NULL) {
                    printf("Value found in the list.\n");
                } else {
                    printf("Value not found in the list.\n");
                }
                break;
            case 9:
                displayDLL(head);
                break;
            case 10:
                destroyDLL(&head);
                printf("List destroyed.\n");
                break;
            case 11:
                destroyDLL(&head);
                exit(0);
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}