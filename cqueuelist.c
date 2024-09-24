#include <stdio.h>
#include <stdlib.h>

// Define the structure for a queue node
struct Node {
    int data;
    struct Node* next;
};

// Function to check if the queue is empty
int isEmpty(struct Node* front) {
    return front == NULL;
}

// Function to enqueue an element into the circular queue
void enqueue(struct Node** front, struct Node** rear, int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
        printf("Queue overflow\n");
        return;
    }
    newNode->data = value;
    newNode->next = NULL;

    if (*rear == NULL) {
        // The queue is empty
        *front = *rear = newNode;
        newNode->next = newNode;  // Point to itself to make it circular
    } else {
        newNode->next = (*rear)->next;  // Point new node to front
        (*rear)->next = newNode;        // Rear's next points to new node
        *rear = newNode;                // Move rear to the new node
    }
    printf("Enqueued %d into the queue\n", value);
}

// Function to dequeue an element from the circular queue
void dequeue(struct Node** front, struct Node** rear) {
    if (isEmpty(*front)) {
        printf("Queue underflow\n");
        return;
    }

    struct Node* temp = *front;
    if (*front == *rear) {
        // There is only one element in the queue
        *front = *rear = NULL;
    } else {
        *front = (*front)->next;
        (*rear)->next = *front;  // Maintain the circular structure
    }
    printf("Dequeued %d from the queue\n", temp->data);
    free(temp);
}

// Function to display the circular queue and front/rear positions
void displayQueue(struct Node* front, struct Node* rear) {
    if (isEmpty(front)) {
        printf("Queue is empty\n");
        return;
    }

    struct Node* temp = front;
    int position = 0;
    printf("Queue content:\n");
    do {
        printf("Position %d: %d\n", position, temp->data);
        temp = temp->next;
        position++;
    } while (temp != front);

    printf("Front is at position: 0\n");
    printf("Rear is at position: %d\n", position - 1);
}

// Main function for menu-driven queue operations
int main() {
    struct Node* front = NULL;
    struct Node* rear = NULL;
    int choice, value;

    do {
        printf("\n--- Circular Queue Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display Queue\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                scanf("%d", &value);
                enqueue(&front, &rear, value);
                displayQueue(front, rear);
                break;
            case 2:
                dequeue(&front, &rear);
                displayQueue(front, rear);
                break;
            case 3:
                displayQueue(front, rear);
                break;
            case 4:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 4);

    return 0;
}