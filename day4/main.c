#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHAR 1000
#define PART1 0
#define PART2 !PART1
#define SAMPLE 0
#define WINNINGSIZE (SAMPLE ? 5 : 10)
#define MYCARDSIZE (SAMPLE ? 8 : 25)
#define ARRAY_SIZE (SAMPLE ? 6 : 213)


int getPoints(const int pInt[WINNINGSIZE], const int pInt1[MYCARDSIZE]);
void AddPointsToCards(int pInt[WINNINGSIZE], int pInt1[MYCARDSIZE], int* totalPoints, int index);
int getNbWinningCards(const int pInt[WINNINGSIZE], const int pInt1[MYCARDSIZE]);

int main(void) {
    FILE* filePointer;
    char line[MAX_CHAR];

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

    char* saveptrGame, *saveptrWinning, *saveptrMyCard;
#if PART1
    int totalPoints = 0;

    // Reading and processing the input file
    while (fgets(line, MAX_CHAR, filePointer) != NULL) {
        char* token;
        int Winning[WINNINGSIZE];
        int MyCard[MYCARDSIZE];
        strtok_r(line, ":", &saveptrGame); // Remove the first part of the string, the game id
        //separate with |
        token = strtok_r(NULL, "|", &saveptrGame);
        //extract the winning numbers separated by space
        token = strtok_r(token, " ", &saveptrWinning);
        int i = 0;
        while (token) {
            Winning[i] = strtol(token, NULL, 10);
            token = strtok_r(NULL, " ", &saveptrWinning);
            i++;
        }

        //second part of the string, my card
        token = strtok_r(NULL, "|", &saveptrGame);
        //extract MyCard numbers separated by space
        token = strtok_r(token, " ", &saveptrMyCard);
        i = 0;
        while (token) {
            MyCard[i] = strtol(token, NULL, 10);
            token = strtok_r(NULL, " ", &saveptrMyCard);
            i++;
        }

        totalPoints += getPoints(Winning, MyCard);
    }
    printf("Total points: %d\n", totalPoints);
#endif
#if PART2
    int* totalPoints = malloc(ARRAY_SIZE * sizeof(int));

    //initialize array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        totalPoints[i] = 0;
    }

    int index = 0;
    // Reading and processing the input file
    while (fgets(line, MAX_CHAR, filePointer) != NULL) {
        char* token;
        int Winning[WINNINGSIZE];
        int MyCard[MYCARDSIZE];

        strtok_r(line, ":", &saveptrGame); // Remove the first part of the string, the game id
        //separate with |
        token = strtok_r(NULL, "|", &saveptrGame);
        //extract the winning numbers separated by space
        token = strtok_r(token, " ", &saveptrWinning);
        int i = 0;
        while (token) {
            Winning[i] = strtol(token, NULL, 10);
            token = strtok_r(NULL, " ", &saveptrWinning);
            i++;
        }

        //second part of the string, my card
        token = strtok_r(NULL, "|", &saveptrGame);
        //extract MyCard numbers separated by space
        token = strtok_r(token, " ", &saveptrMyCard);
        i = 0;
        while (token) {
            MyCard[i] = strtol(token, NULL, 10);
            token = strtok_r(NULL, " ", &saveptrMyCard);
            i++;
        }

        AddPointsToCards(Winning, MyCard, totalPoints, index);
        index++;
    }

    int sum = 0;
    for (int i = 0; i < ARRAY_SIZE; i++) {
        sum += totalPoints[i];
    }
    printf("Total points: %d\n", sum);
    //print array
    for (int i = 0; i < ARRAY_SIZE; i++) {
        //printf("%d ", totalPoints[i]);
    }

    free(totalPoints);
#endif

    fclose(filePointer);
    return 0;
}

void AddPointsToCards(int pInt[WINNINGSIZE], int pInt1[MYCARDSIZE], int* totalPoints, int index) {
    int nbWinningCards = getNbWinningCards(pInt, pInt1);

    if (nbWinningCards == 0) {
        totalPoints[index] += 1;
        return;
    }

    //original card
    for (int i = 1; i < nbWinningCards + 1; i++) {
        totalPoints[index + i] += 1;
    }

    //duplicates
    for (int i = 1; i < nbWinningCards + 1; i++) {
            totalPoints[index + i] += totalPoints[index];
    }

    totalPoints[index] += 1;
}

int getPoints(const int pInt[WINNINGSIZE], const int pInt1[MYCARDSIZE]) {
    int points = 0;
    for (int i = 0; i < MYCARDSIZE; i++) {
        for (int j = 0; j < WINNINGSIZE; j++) {
            if (pInt1[i] == pInt[j]) {
                if (points == 0) {
                    points = 1;
                    break;
                } else {
                    points *= 2;
                    break;
                }
            }
        }
    }
    return points;
}

int getNbWinningCards(const int pInt[WINNINGSIZE], const int pInt1[MYCARDSIZE]) {
    int nbWinningCards = 0;
    for (int i = 0; i < MYCARDSIZE; i++) {
        for (int j = 0; j < WINNINGSIZE; j++) {
            if (pInt1[i] == pInt[j]) {
                nbWinningCards++;
                break;
            }
        }
    }
    return nbWinningCards;
}