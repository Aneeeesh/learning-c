#include <stdio.h>

void tryToChange(int x) {
    x = 999;
}

void actuallyChange(int *x) {
    *x = 999;
}

int main() {
    int number = 10;

    printf("Start: %d\n", number);
    tryToChange(number);
    printf("After tryToChange: %d\n", number);
    actuallyChange(&number);
    printf("After actuallyChange: %d\n", number);

    return 0;
}