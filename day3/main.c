#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CHAR 1000
#define MAX_ROWS 140
#define MAX_COLS 10
#define SAMPLE 1
#define ARRAY_SIZE (SAMPLE ? 10 : MAX_ROWS)

typedef struct {
    int value;
    int positionX;
    int positionY;
    int length;
    bool isPresent;
} NumberFound;

void initializeArrays(NumberFound numbers[MAX_ROWS][MAX_COLS], int symbols[MAX_ROWS][MAX_COLS]);
void processFile(const char *filename, NumberFound numbers[MAX_ROWS][MAX_COLS], int symbols[MAX_ROWS][MAX_COLS]);
void processLine(char *line, NumberFound *ptr, int *symbolIndexes, int rowIndex);
void calculateCloseness(NumberFound numbers[MAX_ROWS][MAX_COLS], int symbolIndexes[MAX_ROWS][MAX_COLS], int rowCount);
void checkClosenessForRow(NumberFound numbers[MAX_ROWS][MAX_COLS], int symbolIndexes[MAX_ROWS][MAX_COLS],
                          int currentRow, int currentCol, int targetRow, bool isDiagonal);

int main(void) {
    NumberFound AllNumbers[MAX_ROWS][MAX_COLS];
    int symbols[MAX_ROWS][MAX_COLS];

    initializeArrays(AllNumbers, symbols);

    const char *filename = "sample.txt";
    processFile(filename, AllNumbers, symbols);
    //print numbers
//    for (int i = 0; i < ARRAY_SIZE; i++) {
//        for (int j = 0; j < MAX_COLS; j++) {
//            if (true) {
//                printf("%d ", AllNumbers[i][j].value);
//            }
//        }
//        printf("\n");
//    }
    calculateCloseness(AllNumbers, symbols, ARRAY_SIZE);

    return 0;
}

void initializeArrays(NumberFound numbers[MAX_ROWS][MAX_COLS], int symbols[MAX_ROWS][MAX_COLS]) {
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            symbols[i][j] = -1;

            NumberFound n = {0, 0, 0, 0, false};
            numbers[i][j] = n;
        }
    }
}

void processFile(const char *filename, NumberFound numbers[MAX_ROWS][MAX_COLS], int symbols[MAX_ROWS][MAX_COLS]) {
    FILE *filePointer;
    char line[MAX_CHAR];
    int index = 0;

    filePointer = fopen(filename, "r");
    if (filePointer == NULL) {
        printf("Could not open file %s", filename);
        exit(1);
    }

    while (fgets(line, MAX_CHAR, filePointer) != NULL) {
        processLine(line, numbers[index], symbols[index], index);
        index++;
    }

    fclose(filePointer);
}

void processLine(char *line, NumberFound *ptr, int *symbolIndexes, int rowIndex) {
    int startIndex = 0;

    while (*line) {
        if (isdigit(*line)) {
            long val = strtol(line, &line, 10);
            NumberFound n = {val, startIndex, rowIndex, (int)floor(log10(abs(val))) + 1, false};
            ptr[startIndex] = n;

            startIndex += n.length;
        } else {
            if (*line != '.' && *line != '\n') {
                symbolIndexes[rowIndex] = startIndex;
            }
            line++;
            startIndex++;
        }
    }
}

void calculateCloseness(NumberFound numbers[MAX_ROWS][MAX_COLS], int symbolIndexes[MAX_ROWS][MAX_COLS], int rowCount) {
    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            if (numbers[row][col].length != 0) {
                checkClosenessForRow(numbers, symbolIndexes, row, col, row - 1, 1); // Check above
                checkClosenessForRow(numbers, symbolIndexes, row, col, row + 1, 1 );// Check below
                checkClosenessForRow(numbers, symbolIndexes, row, col, row, 0);     // Check same row
            }
        }
    }

    int sum = 0;
    for (int row = 0; row < rowCount; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            if (numbers[row][col].isPresent) {
                sum += numbers[row][col].value;
                printf("%d\n", numbers[row][col].value);
            }
        }
    }
    printf("sum = %d\n", sum);
}

void checkClosenessForRow(NumberFound numbers[MAX_ROWS][MAX_COLS], int symbolIndexes[MAX_ROWS][MAX_COLS],
                          int currentRow, int currentCol, int targetRow, bool isDiagonal) {
    for (int k = 0; k < MAX_COLS; k++) {
        if (isDiagonal) {
            if (symbolIndexes[targetRow][k] >= numbers[currentRow][currentCol].positionX - 1 &&
                symbolIndexes[targetRow][k] <= numbers[currentRow][currentCol].positionX + numbers[currentRow][currentCol].length) {
                numbers[currentRow][currentCol].isPresent = true;
                return;
            }
        } else {
            if (symbolIndexes[targetRow][k] == numbers[currentRow][currentCol].positionX - 1 ||
                symbolIndexes[targetRow][k] == numbers[currentRow][currentCol].positionX + numbers[currentRow][currentCol].length) {
                numbers[currentRow][currentCol].isPresent = true;
                return;
            }
        }
    }
}