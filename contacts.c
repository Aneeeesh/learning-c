#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "contacts.txt"

// Node structure
typedef struct Node {
    char name[50];
    char phone[20];
    char email[50];
    struct Node *next;
} Node;

// Create a new node
Node* createNode(char *name, char *phone, char *email) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newNode->name, name);
    strcpy(newNode->phone, phone);
    strcpy(newNode->email, email);
    newNode->next = NULL;
    return newNode;
}

// Add contact to linked list
void addContact(Node **head, char *name, char *phone, char *email) {
    Node *newNode = createNode(name, phone, email);
    if (*head == NULL) {
        *head = newNode;
    } else {
        Node *temp = *head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
    printf("Contact added!\n");
}

// Display all contacts
void displayAll(Node *head) {
    if (head == NULL) {
        printf("\nNo contacts yet!\n");
        return;
    }
    int count = 1;
    printf("\n%-5s %-20s %-15s %-30s\n", "No.", "Name", "Phone", "Email");
    printf("------------------------------------------------------------\n");
    Node *temp = head;
    while (temp != NULL) {
        printf("%-5d %-20s %-15s %-30s\n",
            count++,
            temp->name,
            temp->phone,
            temp->email);
        temp = temp->next;
    }
}

// Search contact by name
void searchContact(Node *head, char *name) {
    Node *temp = head;
    int found = 0;
    while (temp != NULL) {
        if (strstr(temp->name, name) != NULL) {
            printf("\nFound: %s | %s | %s\n",
                temp->name, temp->phone, temp->email);
            found = 1;
        }
        temp = temp->next;
    }
    if (!found)
        printf("\nNo contact found with name '%s'\n", name);
}

// Delete contact by name
void deleteContact(Node **head, char *name) {
    if (*head == NULL) {
        printf("\nList is empty!\n");
        return;
    }
    // If head needs to be deleted
    if (strcmp((*head)->name, name) == 0) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);
        printf("\nContact deleted!\n");
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        if (strcmp(temp->next->name, name) == 0) {
            Node *toDelete = temp->next;
            temp->next = temp->next->next;
            free(toDelete);
            printf("\nContact deleted!\n");
            return;
        }
        temp = temp->next;
    }
    printf("\nContact '%s' not found!\n", name);
}

// Save all contacts to file
void saveToFile(Node *head) {
    FILE *file = fopen(FILENAME, "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }
    Node *temp = head;
    int count = 0;
    while (temp != NULL) {
        fprintf(file, "%s|%s|%s\n",
            temp->name, temp->phone, temp->email);
        count++;
        temp = temp->next;
    }
    fclose(file);
    printf("\n%d contacts saved to file!\n", count);
}

// Load contacts from file into linked list
void loadFromFile(Node **head) {
    FILE *file = fopen(FILENAME, "r");
    if (file == NULL) {
        printf("No saved contacts found.\n");
        return;
    }
    char line[120];
    int count = 0;
    while (fgets(line, sizeof(line), file)) {
        // Remove newline at end
        line[strcspn(line, "\n")] = 0;

        // Split line by | separator
        char *name  = strtok(line, "|");
        char *phone = strtok(NULL, "|");
        char *email = strtok(NULL, "|");

        if (name && phone && email) {
            addContact(head, name, phone, email);
            count++;
        }
    }
    fclose(file);
    printf("%d contacts loaded from file!\n", count);
}

// Free all memory
void freeList(Node **head) {
    Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int main() {
    Node *head = NULL;
    int choice;
    char name[50], phone[20], email[50];

    printf("================================\n");
    printf("     Mini Contacts Database     \n");
    printf("================================\n");

    // Load existing contacts on startup
    printf("\nLoading saved contacts...\n");
    loadFromFile(&head);

    while (1) {
        printf("\n1. Add Contact\n");
        printf("2. Display All\n");
        printf("3. Search Contact\n");
        printf("4. Delete Contact\n");
        printf("5. Save to File\n");
        printf("6. Exit\n");
        printf("\nEnter choice: ");
        fflush(stdout);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fflush(stdout);
                scanf(" %[^\n]", name);
                printf("Enter phone: ");
                fflush(stdout);
                scanf(" %[^\n]", phone);
                printf("Enter email: ");
                fflush(stdout);
                scanf(" %[^\n]", email);
                addContact(&head, name, phone, email);
                break;

            case 2:
                displayAll(head);
                break;

            case 3:
                printf("Enter name to search: ");
                fflush(stdout);
                scanf(" %[^\n]", name);
                searchContact(head, name);
                break;

            case 4:
                printf("Enter name to delete: ");
                fflush(stdout);
                scanf(" %[^\n]", name);
                deleteContact(&head, name);
                break;

            case 5:
                saveToFile(head);
                break;

            case 6:
                printf("\nSaving before exit...\n");
                saveToFile(head);
                freeList(&head);
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice!\n");
        }
    }
}
/*
```

4. Press **Ctrl + S**

---

Compile and run:
```
gcc contacts.c -o contacts
.\contacts.exe
*/