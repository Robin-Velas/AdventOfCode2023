#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 1000
#define PART1 0
#define PART2 !PART1
#define SAMPLE 0
#define ARRAY_SIZE (SAMPLE ? 5 : 100)

typedef struct {
    int mRed;
    int mGreen;
    int mBlue;
    int mPowSet;
    int mId;
} Game;

// Function declarations
void addToGameArray(Game* pArray, char* pLine, int index);
int findSumOfGameIdsFittingIntoLimit(Game* array, int limitRed, int limitGreen, int limitBlue);
int findSumOfPowerSet(Game* array);
void initializeGames(Game* array);

int main(void) {
    FILE* filePointer;
    char line[MAX_CHAR];
    Game* gameArray = malloc(ARRAY_SIZE * sizeof(Game));

    initializeGames(gameArray);

#if SAMPLE
    char* filename = "sample.txt";
#else
    char* filename = "input.txt";
#endif

    filePointer = fopen(filename, "r");
    if (filePointer == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    int index = 0;
    char* saveptrGame;

    // Reading and processing the input file
    while (fgets(line, MAX_CHAR, filePointer) != NULL) {
        char* token;
        strtok_r(line, ":", &saveptrGame); // Remove the first part of the string, the game id

        token = strtok_r(NULL, ";", &saveptrGame);

        while (token) {
            // Remove leading space, if any
            while (*token == ' ') {
                token++;
            }

            addToGameArray(gameArray, token, index);
            token = strtok_r(NULL, ";", &saveptrGame);
        }
        index++;
    }

#if PART1
    int sum = findSumOfGameIdsFittingIntoLimit(gameArray, 12, 13, 14);
    printf("Sum of game ids fitting into limit: %d\n", sum);
#endif

#if PART2
    int sum = findSumOfPowerSet(gameArray);
    printf("Sum of power set: %d\n", sum);
#endif

    fclose(filePointer);
    free(gameArray);

    return 0;
}

// Function to calculate the sum of the power set values
int findSumOfPowerSet(Game* array) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        sum += array[i].mPowSet;
    }
    return sum;
}

// Function to initialize the game array
void initializeGames(Game* array) {
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        array[i] = (Game) {0, 0, 0, 0, 0};
    }
}

// Function to find the sum of game IDs fitting into a specified limit
int findSumOfGameIdsFittingIntoLimit(Game* array, int limitRed, int limitGreen, int limitBlue) {
    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; ++i) {
        if (array[i].mRed <= limitRed &&
            array[i].mGreen <= limitGreen &&
            array[i].mBlue <= limitBlue) {
            sum += array[i].mId;
        }
    }
    return sum;
}

// Function to add game data to the array
void addToGameArray(Game* pArray, char* pLine, int index) {
    char* token;
    char* saveptrColors;
    char* saveptrSeparateNumberAndColor;
    char* endptr;

    token = strtok_r(pLine, ",", &saveptrColors);
    pArray[index].mId = index + 1; // ID starts at 1

    while (token != NULL) {
        char* number = strtok_r(token, " ", &saveptrSeparateNumberAndColor);
        char* color = strtok_r(NULL, " ", &saveptrSeparateNumberAndColor);

        if (number != NULL && color != NULL) {
            int value = strtol(number, &endptr, 10);

            if (strstr(color, "red") != NULL && value > pArray[index].mRed) {
                pArray[index].mRed = value;
            } else if (strstr(color, "green") != NULL && value > pArray[index].mGreen) {
                pArray[index].mGreen = value;
            } else if (strstr(color, "blue") != NULL && value > pArray[index].mBlue) {
                pArray[index].mBlue = value;
            }
        }

        token = strtok_r(NULL, ",", &saveptrColors);
    }

    pArray[index].mPowSet = pArray[index].mRed * pArray[index].mGreen * pArray[index].mBlue;
}