#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 100

// Struct - like a blueprint for a student
typedef struct {
    char name[50];
    int roll_number;
    float grades[5];
    float average;
} Student;

// Function to calculate average
float calculateAverage(float grades[], int count) {
    float sum = 0;
    for (int i = 0; i < count; i++) {
        sum += grades[i];
    }
    return sum / count;
}

// Function to get letter grade
const char* getLetterGrade(float average) {
    if (average >= 90) return "A";
    else if (average >= 80) return "B";
    else if (average >= 70) return "C";
    else if (average >= 60) return "D";
    else if (average >= 50) return "E+";
    else if (average >= 40) return "E";
    else if (average >= 30) return "E-";
    else return "F";
}

// Function to add a student
void addStudent(Student students[], int *count) {
    Student s;
    printf("\nEnter student name: ");
    fflush(stdout);
    scanf(" %[^\n]", s.name);
    printf("Enter roll number: ");
    fflush(stdout);
    scanf("%d", &s.roll_number);

    printf("Enter 5 grades (0-100):\n");
    fflush(stdout);
    for (int i = 0; i < 5; i++) {
        printf("  Grade %d: ", i + 1);
        fflush(stdout);
        scanf("%f", &s.grades[i]);
    }

    s.average = calculateAverage(s.grades, 5);
    students[*count] = s;
    (*count)++;
    printf("\n✓ 3Student added successfully!\n");
    fflush(stdout);
}

// Function to display all students
void displayStudents(Student students[], int count) {
    if (count == 0) {
        printf("\nNo students added yet!\n");
        return;
    }

    printf("\n%-20s %-12s %-10s %-6s\n", "Name", "Roll Number", "Average", "Grade");
    printf("----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        printf("%-20s %-12d %-10.2f %-6s\n",
            students[i].name,
            students[i].roll_number,
            students[i].average,
            getLetterGrade(students[i].average));
    }
}

// Function to save to file
void saveToFile(Student students[], int count) {
    FILE *file = fopen("students.txt", "w");
    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    fprintf(file, "%-20s %-12s %-10s %-6s\n", "Name", "Roll Number", "Average", "Grade");
    fprintf(file, "----------------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        fprintf(file, "%-20s %-12d %-10.2f %-6s\n",
            students[i].name,
            students[i].roll_number,
            students[i].average,
            getLetterGrade(students[i].average));
    }

    fclose(file);
    printf("\n✓ Data saved to students.txt!\n");
}

// Function to find top student
void findTopStudent(Student students[], int count) {
    if (count == 0) {
        printf("\nNo students added yet!\n");
        return;
    }

    int topIndex = 0;
    for (int i = 1; i < count; i++) {
        if (students[i].average > students[topIndex].average) {
            topIndex = i;
        }
    }

    printf("\n Top Student: %s with average %.2f (%s)\n",
        students[topIndex].name,
        students[topIndex].average,
        getLetterGrade(students[topIndex].average));
}

int main() {
    Student students[MAX_STUDENTS];
    int count = 0;
    int choice;

    printf("================================\n");
    printf("   Student Grade Manager v1.0   \n");
    printf("================================\n");
    fflush(stdout);

    while (1) {
        printf("\n1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Find Top Student\n");
        printf("4. Save to File\n");
        printf("5. Exit\n");
        printf("\nEnter choice: ");
        fflush(stdout);
        
        if(scanf("%d", &choice) != 1) {
            printf("Invalid input!\n");
            fflush(stdout);
            continue;
        }

        switch (choice) {
            case 1: addStudent(students, &count); break;
            case 2: displayStudents(students, count); break;
            case 3: findTopStudent(students, count); break;
            case 4: saveToFile(students, count); break;
            case 5:
                printf("\nGoodbye! Keep coding!\n");
                fflush(stdout);
                return 0;
            default:
                printf("Invalid choice!\n");
                fflush(stdout);
        }
    }

    return 0;
}