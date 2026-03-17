#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ================================
//            STACK
// ================================

typedef struct StackNode {
    int data;
    struct StackNode *next;
} StackNode;

// Push - add to top
void push(StackNode **top, int data) {
    StackNode *newNode = (StackNode*)malloc(sizeof(StackNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    newNode->next = *top;  // new node points to old top
    *top = newNode;        // new node becomes the top
    printf("Pushed %d to stack!\n", data);
}

// Pop - remove from top
int pop(StackNode **top) {
    if (*top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    StackNode *temp = *top;
    int data = temp->data;
    *top = (*top)->next;  // move top down
    free(temp);
    return data;
}

// Peek - see top without removing
int peek(StackNode *top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return -1;
    }
    return top->data;
}

// Display stack
void displayStack(StackNode *top) {
    if (top == NULL) {
        printf("Stack is empty!\n");
        return;
    }
    printf("Stack (top to bottom): ");
    StackNode *temp = top;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// ================================
//            QUEUE
// ================================

typedef struct QueueNode {
    int data;
    struct QueueNode *next;
} QueueNode;

typedef struct {
    QueueNode *front;  // remove from here
    QueueNode *rear;   // add from here
} Queue;

// Initialize empty queue
void initQueue(Queue *q) {
    q->front = NULL;
    q->rear = NULL;
}

// Enqueue - add to rear
void enqueue(Queue *q, int data) {
    QueueNode *newNode = (QueueNode*)malloc(sizeof(QueueNode));
    if (newNode == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (q->rear == NULL) {
        q->front = newNode;
        q->rear = newNode;
    } else {
        q->rear->next = newNode;  // add to rear
        q->rear = newNode;        // update rear
    }
    printf("Enqueued %d to queue!\n", data);
}

// Dequeue - remove from front
int dequeue(Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return -1;
    }
    QueueNode *temp = q->front;
    int data = temp->data;
    q->front = q->front->next;  // move front forward
    if (q->front == NULL)
        q->rear = NULL;         // queue is now empty
    free(temp);
    return data;
}

// Display queue
void displayQueue(Queue *q) {
    if (q->front == NULL) {
        printf("Queue is empty!\n");
        return;
    }
    printf("Queue (front to rear): ");
    QueueNode *temp = q->front;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// ================================
//            MAIN MENU
// ================================

int main() {
    StackNode *top = NULL;  // empty stack
    Queue q;
    initQueue(&q);          // empty queue

    int choice, data;

    printf("================================\n");
    printf("      Stack & Queue in C        \n");
    printf("================================\n");

    while (1) {
        printf("\n--- STACK ---\n");
        printf("1. Push to Stack\n");
        printf("2. Pop from Stack\n");
        printf("3. Peek Stack\n");
        printf("4. Display Stack\n");
        printf("\n--- QUEUE ---\n");
        printf("5. Enqueue\n");
        printf("6. Dequeue\n");
        printf("7. Display Queue\n");
        printf("\n8. Exit\n");
        printf("\nEnter choice: ");
        fflush(stdout);
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter number to push: ");
                fflush(stdout);
                scanf("%d", &data);
                push(&top, data);
                break;

            case 2:
                data = pop(&top);
                if (data != -1)
                    printf("Popped: %d\n", data);
                break;

            case 3:
                data = peek(top);
                if (data != -1)
                    printf("Top of stack: %d\n", data);
                break;

            case 4:
                displayStack(top);
                break;

            case 5:
                printf("Enter number to enqueue: ");
                fflush(stdout);
                scanf("%d", &data);
                enqueue(&q, data);
                break;

            case 6:
                data = dequeue(&q);
                if (data != -1)
                    printf("Dequeued: %d\n", data);
                break;

            case 7:
                displayQueue(&q);
                break;

            case 8:
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

Compile and run:
```
gcc stack_queue.c -o stack_queue
.\stack_queue.exe
*/