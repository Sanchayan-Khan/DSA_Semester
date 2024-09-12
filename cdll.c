#include<stdio.h>
#include<stdlib.h>

struct node {
    int data;
    struct node* next;
    struct node* prev;
};

// Create a circular doubly linked list
void createList(struct node** head) {
    int n, d;
    struct node* newnode;
    struct node* temp;
    printf("Enter the number of nodes: \n");
    scanf("%d", &n);
    if (n <= 0) {
        printf("Invalid number of nodes\n");
        return;
    }
    for(int i = 0; i < n; i++) {
        printf("\nEnter the data at position %d: ", i + 1);
        scanf("%d", &d);
        newnode = (struct node*)malloc(sizeof(struct node));
        newnode->data = d;
        newnode->next = newnode->prev = NULL;
        if(*head == NULL) {
            *head = newnode;
            newnode->next = newnode->prev = *head;
            temp = *head;
        } else {
            newnode->prev = temp;
            newnode->next = *head;
            temp->next = newnode;
            (*head)->prev = newnode;
            temp = newnode;
        }
    }
}

// Insert at the beginning
void insertatbegin(struct node** head) {
    struct node* newnode; 
    struct node* temp;
    int d;
    printf("\nEnter the data: ");
    scanf("%d", &d);
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = d;
    newnode->next = newnode->prev = NULL;
    if(*head == NULL) {
        *head = newnode;
        newnode->next = newnode->prev = *head;
    } else {
        temp = *head;
        while(temp->next != *head) {
            temp = temp->next;
        }
        newnode->next = *head;
        newnode->prev = temp;
        temp->next = newnode;
        (*head)->prev = newnode;
        *head = newnode;
    }
}

// Insert at the end
void insertatend(struct node** head) {
    struct node* newnode; 
    struct node* temp;
    int d;
    printf("\nEnter the data: ");
    scanf("%d", &d);
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = d;
    newnode->next = newnode->prev = NULL;
    if(*head == NULL) {
        *head = newnode;
        newnode->next = newnode->prev = *head;
    } else {
        temp = *head;
        while(temp->next != *head) {
            temp = temp->next;
        }
        newnode->next = *head;
        newnode->prev = temp;
        temp->next = newnode;
        (*head)->prev = newnode;
    }
}

// Insert after a given position
void insertafterpos(struct node** head, int pos) {
    struct node* newnode;
    struct node* temp;
    int d, i = 1;
    if(*head == NULL) {
        printf("\nList is empty");
        return;
    }
    printf("\nEnter the data: ");
    scanf("%d", &d);
    newnode = (struct node*)malloc(sizeof(struct node));
    newnode->data = d;
    temp = *head;
    while(i < pos && temp->next != *head) {
        temp = temp->next;
        i++;
    }
    newnode->next = temp->next;
    newnode->prev = temp;
    temp->next->prev = newnode;
    temp->next = newnode;
}

// Insert before a given position
void insertbeforepos(struct node** head, int pos) {
    if(pos == 1) {
        insertatbegin(head);
        return;
    }
    insertafterpos(head, pos - 1);
}

// Delete after a given position
void deleteafterpos(struct node** head, int pos) {
    struct node* temp = *head;
    struct node* delnode;
    int i = 1;
    if(*head == NULL) {
        printf("\nList is empty");
        return;
    }
    while(i < pos && temp->next != *head) {
        temp = temp->next;
        i++;
    }
    if(temp->next == *head) {
        printf("\nNo node exists after position %d", pos);
        return;
    }
    delnode = temp->next;
    temp->next = delnode->next;
    delnode->next->prev = temp;
    free(delnode);
}

// Delete from the end
void deletefromend(struct node** head) {
    struct node* temp = *head;
    if(*head == NULL) {
        printf("\nList is empty");
        return;
    }
    while(temp->next != *head) {
        temp = temp->next;
    }
    if(temp == *head) {
        free(*head);
        *head = NULL;
    } else {
        temp->prev->next = *head;
        (*head)->prev = temp->prev;
        free(temp);
    }
}

// Delete from the beginning
void deletefrombegin(struct node** head) {
    struct node* temp = *head;
    if(*head == NULL) {
        printf("\nList is empty");
        return;
    }
    while(temp->next != *head) {
        temp = temp->next;
    }
    if(*head == temp) {
        free(*head);
        *head = NULL;
    } else {
        temp->next = (*head)->next;
        (*head)->next->prev = temp;
        free(*head);
        *head = temp->next;
    }
}

// Search for a value
void search(struct node* head, int key) {
    struct node* temp = head;
    int pos = 1;
    if(head == NULL) {
        printf("\nList is empty");
        return;
    }
    do {
        if(temp->data == key) {
            printf("\nValue %d found at position %d", key, pos);
            return;
        }
        temp = temp->next;
        pos++;
    } while(temp != head);
    printf("\nValue %d not found in the list", key);
}

// Destroy the circular doubly linked list
void destroylist(struct node** head) {
    struct node* temp = *head;
    struct node* nextnode;
    if(*head == NULL) return;
    while(temp->next != *head) {
        nextnode = temp->next;
        free(temp);
        temp = nextnode;
    }
    free(temp);
    *head = NULL;
}

// Display the circular doubly linked list
void printlist(struct node* head) {
    struct node* temp = head;
    if(head == NULL) {
        printf("\nList is empty");
        return;
    }
    do {
        printf("%d\t", temp->data);
        temp = temp->next;
    } while(temp != head);
    printf("\n");
}

void main() {
    struct node* head = NULL;
    int pos, val;
    while(1) {
        printf("\n1.Create list");
        printf("\n2.Display List");
        printf("\n3.Insert at beginning");
        printf("\n4.Insert at end");
        printf("\n5.Insert after position");
        printf("\n6.Insert before position");
        printf("\n7.Delete after position");
        printf("\n8.Delete from beginning");
        printf("\n9.Delete from end");
        printf("\n10.Search");
        printf("\n11.Destroy list");
        printf("\n12.Exit");
        printf("\nEnter choice: ");
        int ch;
        scanf("%d", &ch);
        switch(ch) {
            case 1: createList(&head); break;
            case 2: printlist(head); break;
            case 3: insertatbegin(&head); break;
            case 4: insertatend(&head); break;
            case 5: 
                printf("\nEnter position: ");
                scanf("%d", &pos);
                insertafterpos(&head, pos);
                break;
            case 6: 
                printf("\nEnter position: ");
                scanf("%d", &pos);
                insertbeforepos(&head, pos);
                break;
            case 7: 
                printf("\nEnter position: ");
                scanf("%d", &pos);
                deleteafterpos(&head, pos);
                break;
            case 8: deletefrombegin(&head); break;
            case 9: deletefromend(&head); break;
            case 10: 
                printf("\nEnter value to search: ");
                scanf("%d", &val);
                search(head, val);
                break;
            case 11: destroylist(&head); break;
            case 12: exit(0);
            default: printf("\nWrong Input! Enter again\n");
        }
        printlist(head);
    }
}