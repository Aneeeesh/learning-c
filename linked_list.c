#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// NODE - the building block of our linked list
typedef struct Node {
    char name[50];
    int roll_number;
    float gpa;
    struct Node *next;  // pointer to next node
} Node;

// Create a new node using malloc
Node* createNode(char *name, int roll, float gpa) {
    Node *newNode = (Node*)malloc(sizeof(Node));  // book memory
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }
    strcpy(newNode->name, name);
    newNode->roll_number = roll;
    newNode->gpa = gpa;
    newNode->next = NULL;  // no next node yet
    return newNode;
}

// Add student at the end of the list
void addStudent(Node **head, char *name, int roll, float gpa) {
    Node *newNode = createNode(name, roll, gpa);

    // If list is empty, new node becomes the head
    if (*head == NULL) {
        *head = newNode;
        printf("Student added as first record!\n");
        return;
    }

    // Otherwise travel to the end and add there
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;  // move to next node
    }
    temp->next = newNode;
    printf("Student added successfully!\n");
}

// Display all students
void displayAll(Node *head) {
    if (head == NULL) {
        printf("\nNo students yet!\n");
        return;
    }

    printf("\n%-5s %-20s %-10s\n", "Roll", "Name", "GPA");
    printf("------------------------------------\n");

    Node *temp = head;
    while (temp != NULL) {
        printf("%-5d %-20s %-10.2f\n",
            temp->roll_number,
            temp->name,
            temp->gpa);
        temp = temp->next;  // move to next node
    }
}

// Search for a student by name
void searchStudent(Node *head, char *name) {
    Node *temp = head;
    while (temp != NULL) {
        if (strcmp(temp->name, name) == 0) {
            printf("\nFound! Roll: %d | Name: %s | GPA: %.2f\n",
                temp->roll_number,
                temp->name,
                temp->gpa);
            return;
        }
        temp = temp->next;
    }
    printf("\nStudent '%s' not found!\n", name);
}

// Delete a student by roll number
void deleteStudent(Node **head, int roll) {
    if (*head == NULL) {
        printf("\nList is empty!\n");
        return;
    }

    // If head node is the one to delete
    if ((*head)->roll_number == roll) {
        Node *temp = *head;
        *head = (*head)->next;
        free(temp);  // free memory!
        printf("\nStudent deleted!\n");
        return;
    }

    // Search for the node to delete
    Node *temp = *head;
    while (temp->next != NULL) {
        if (temp->next->roll_number == roll) {
            Node *toDelete = temp->next;
            temp->next = temp->next->next;  // skip over deleted node
            free(toDelete);  // free memory!
            printf("\nStudent deleted!\n");
            return;
        }
        temp = temp->next;
    }
    printf("\nStudent with roll %d not found!\n", roll);
}

// Count total students
int countStudents(Node *head) {
    int count = 0;
    Node *temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// Free all memory at end
void freeList(Node **head) {
    Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
    printf("\nMemory freed!\n");
}

int main() {
    Node *head = NULL;  // empty list
    int choice, roll;
    float gpa;
    char name[50];

    printf("================================\n");
    printf("   Student Records System       \n");
    printf("   Using Linked List            \n");
    printf("================================\n");

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Display All\n");
        printf("3. Search Student\n");
        printf("4. Delete Student\n");
        printf("5. Count Students\n");
        printf("6. Exit\n");
        printf("\nEnter choice: ");
        fflush(stdout);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                fflush(stdout);
                scanf(" %[^\n]", name);
                printf("Enter roll number: ");
                fflush(stdout);
                scanf("%d", &roll);
                printf("Enter GPA: ");
                fflush(stdout);
                scanf("%f", &gpa);
                addStudent(&head, name, roll, gpa);
                break;

            case 2:
                displayAll(head);
                break;

            case 3:
                printf("Enter name to search: ");
                fflush(stdout);
                scanf(" %[^\n]", name);
                searchStudent(head, name);
                break;

            case 4:
                printf("Enter roll number to delete: ");
                fflush(stdout);
                scanf("%d", &roll);
                deleteStudent(&head, roll);
                break;

            case 5:
                printf("\nTotal students: %d\n", countStudents(head));
                break;

            case 6:
                freeList(&head);
                printf("\nGoodbye!\n");
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

### What's new in this code:
| Concept | What it does |
|---------|-------------|
| `malloc` | Books memory for a new node |
| `free` | Returns memory when deleting |
| `struct Node *next` | Pointer to next node in chain |
| `**head` | Pointer to pointer (to modify the list itself) |
| `->` | Access struct members through a pointer |

---

Compile and run:
```
gcc linked_list.c -o linked_list
.\linked_list.exe
*/