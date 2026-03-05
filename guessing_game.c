#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Pointer practice - generate random number and store in pointer
void generateNumber(int *secret, int max) {
    *secret = (rand() % max) + 1;
}

// Pointer practice - update attempts using pointer
void incrementAttempts(int *attempts) {
    (*attempts)++;
}

// Give hint using pointer to secret number
void giveHint(int guess, int *secret) {
    if (guess < *secret)
        printf("Too LOW! Go higher! \n");
    else if (guess > *secret)
        printf("Too HIGH! Go lower! \n");
}

// Save high score to file
void saveHighScore(char *name, int attempts, int difficulty) {
    FILE *file = fopen("highscore.txt", "w");
    if (file == NULL) return;

    fprintf(file, "Player: %s\n", name);
    fprintf(file, "Attempts: %d\n", attempts);
    fprintf(file, "Difficulty: %d\n", difficulty);
    fclose(file);
    printf("High score saved!\n");
}

// Load and show high score
void showHighScore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file == NULL) {
        printf("No high score yet!\n");
        return;
    }

    char line[100];
    printf("\n--- HIGH SCORE ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    printf("------------------\n");
    fclose(file);
}

int main() {
    srand(time(NULL)); // seed random number

    int secret = 0;
    int guess = 0;
    int attempts = 0;
    int maxNumber = 0;
    int choice = 0;
    char name[50];

    printf("================================\n");
    printf("     Number Guessing Game!      \n");
    printf("================================\n");

    printf("\nEnter your name: ");
    fflush(stdout);
    scanf(" %[^\n]", name);

    printf("\nChoose difficulty:\n");
    printf("1. Easy   (1-10)\n");
    printf("2. Medium (1-50)\n");
    printf("3. Hard   (1-100)\n");
    printf("Enter choice: ");
    fflush(stdout);
    scanf("%d", &choice);

    switch (choice) {
        case 1: maxNumber = 10; break;
        case 2: maxNumber = 50; break;
        case 3: maxNumber = 100; break;
        default: maxNumber = 50;
    }

    // Using pointer to generate secret number
    generateNumber(&secret, maxNumber);

    printf("\nGuess a number between 1 and %d\n", maxNumber);
    printf("Good luck %s!\n\n", name);

    while (guess != secret) {
        printf("Attempt %d - Enter guess: ", attempts + 1);
        fflush(stdout);
        scanf("%d", &guess);

        if (guess == secret) {
            printf("\nCORRECT! You got it in %d attempts!\n", attempts + 1);

            // Save if its a good score
            saveHighScore(name, attempts + 1, maxNumber);
        } else {
            // Using pointer to give hint
            giveHint(guess, &secret);
            // Using pointer to track attempts
            incrementAttempts(&attempts);
        }
    }

    // Show high score at end
    showHighScore();

    return 0;
}

/*
4. Press **Ctrl + S**

---

Compile and run:
```
gcc guessing_game.c -o guessing_game
.\guessing_game.exe*/