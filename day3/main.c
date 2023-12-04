#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#define MAX_CHAR 1000
#define SAMPLE 0
#define MAX_ROWS (SAMPLE ? 10 : 140)
#define MAX_COLS (SAMPLE ? 10 : 140)
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
int searchSum(NumberFound numbers[MAX_ROWS][MAX_COLS], int yIndex, int xIndex);
bool isClose(NumberFound param, int xIndex, bool isUpperOrLowerRow);

int main(void) {
    NumberFound AllNumbers[MAX_ROWS][MAX_COLS];
    int symbols[MAX_ROWS][MAX_COLS];

    initializeArrays(AllNumbers, symbols);
#if SAMPLE == 1
    const char *filename = "sample.txt";
#else
    const char *filename = "input.txt";
#endif
    processFile(filename, AllNumbers, symbols);

    //for each symbol, check the rows above, below, and the same row.
    //if 2 numbers are found, * them and add to the total

    int total = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            if (symbols[i][j] != -1) { //symbol found
                //printf("symbol x:%d y:%d\n", j, i);
                total += searchSum(AllNumbers, i, j);
            }
        }
    }
    printf("Total: %d\n", total);

    return 0;
}

int searchSum(NumberFound numbers[MAX_ROWS][MAX_COLS], int yIndex, int xIndex) {
    int sum = 0;
    int nbNumbersFound = 0; //we need 2 numbers to calculate the sum

    //calibrate the start and end row indexes
    int startRow = yIndex == 0 ? yIndex : yIndex - 1;
    int endRow = yIndex == ARRAY_SIZE - 1 ? yIndex : yIndex + 1;

    for (int y = startRow; y <= endRow; y++) { //check the row above, the same row, and the row below
        for (int i = 0; i < MAX_COLS; i++) { //check all the columns
            if ( numbers[y][i].isPresent && isClose(numbers[y][i], xIndex, y != yIndex) ) {
                switch (nbNumbersFound) {
                    case 0: {
                        sum = numbers[y][i].value;
                    }
                        break;
                    case 1: {
                        printf("Found 2 numbers: %d and %d\n", sum, numbers[y][i].value);
                        sum *= numbers[y][i].value;
                        return sum;
                    }
                        break;
                    default:
                        return sum;
                }
                nbNumbersFound++;
            }
        }
    }

    return 0;
}

bool isClose(NumberFound param, int xIndex, bool isUpperOrLowerRow) {
    if (isUpperOrLowerRow) {
        return ((param.positionX <= xIndex && param.positionX + param.length >= xIndex) // if the symbol is in the middle of the number
               ||
                param.positionX + param.length == xIndex // it it's touching to the left side
               ||
                param.positionX == xIndex + 1); //if it's touching to the right side
    } else { //same row
        return (param.positionX == xIndex + 1 ||
                param.positionX + param.length == xIndex);
    }
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
            NumberFound n = {val, startIndex, rowIndex, (int)floor(log10(abs(val))) + 1, true};
            ptr[startIndex] = n;

            startIndex += n.length;
        } else {
            if (*line == '*') {
                symbolIndexes[startIndex] = 1; //symbol found
            }
            line++;
            startIndex++;
        }
    }
}