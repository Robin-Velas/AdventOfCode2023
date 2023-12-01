#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
#define NOT_FOUND -1
#define PART1 0
#define PART2 !PART1
#define SAMPLE 0

int extractIntFromString(char* str);
int extractIntAndStringFromString(char* str);
int main(void)
{
    FILE *fp;
    char str[MAXCHAR];
    #if SAMPLE
    char* filename = "sample.txt";
    #else
    char* filename = "input.txt";
    #endif

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Could not open file %s", filename);
        return 1;
    }

    int sum = 0;
    while (fgets(str, MAXCHAR, fp) != NULL) {
        #if PART1
        int num = extractIntFromString(str);
        #elif PART2
        int num = extractIntAndStringFromString(str);
        #endif
        printf("%d\n", num);
        if (num != -1) {
            sum += num;
        }
    }
    printf("%d\n", sum);
    fclose(fp);

    return 0;
}

int extractIntFromString(char* str)
{
    int first = -1;
    int last = -1;
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] >= '0' && str[i] <= '9') {
            if (first == NOT_FOUND) {
                first = str[i] - '0';
            } else {
                last = str[i] - '0';
            }
        }
    }
    if (last == -1 && first != -1) {
        last = first;
    } 
    if (first != -1 && last != -1) {
        return first * 10 + last;
    }
    return -1;
}

int extractIntAndStringFromString(char* str)
{
    char one[3] = "one";
    char two[3] = "two";
    char three[5] = "three";
    char four[4] = "four";
    char five[4] = "five";
    char six[3] = "six";
    char seven[5] = "seven";
    char eight[5] = "eight";
    char nine[4] = "nine";

    int first = -1;
    int last = -1;

    char* curr = NULL;

    for (int i = 0; i < strlen(str); i++) {
        // we deal with numbers
        if (str[i] >= '0' && str[i] <= '9') {
            if (first == -1) {
                first = str[i] - '0';
            } else {
                last = str[i] - '0';
            }
        } else { // we deal with chars
            curr = &str[i];
            int* currVal = first == -1 ? &first : &last;
            if (strncmp(curr, one, 3) == 0) {
                *currVal = 1;
            } else if (strncmp(curr, two, 3) == 0) {
                *currVal = 2;
            } else if (strncmp(curr, three, 5) == 0) {
                *currVal = 3;
            } else if (strncmp(curr, four, 4) == 0) {
                *currVal = 4;
            } else if (strncmp(curr, five, 4) == 0) {
                *currVal = 5;
            } else if (strncmp(curr, six, 3) == 0) {
                *currVal = 6;
            } else if (strncmp(curr, seven, 5) == 0) {
                *currVal = 7;
            } else if (strncmp(curr, eight, 5) == 0) {
                *currVal = 8;
            } else if (strncmp(curr, nine, 4) == 0) {
                *currVal = 9;
            }
        }
    }
    if (last == -1 && first != -1) {
        last = first;
    }
    if (first != -1 && last != -1) {
        return first * 10 + last;
    }
    return -1;
}