#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define SAMPLE 0
#define MAX_READINGS 1000
#define MAX_READING_SIZE 100

typedef struct {
    long values[MAX_READING_SIZE];
    int size;
} Reading;

typedef struct {
    Reading readings[MAX_READINGS];
    int size;
} Readings;

int recursionSum( Reading reading ) {
    
    int allZero = 1;
    
    for (int i = 0; i < reading.size; i++) {
        if (reading.values[i] != 0) {
            allZero = 0;
        }
    }

    if (allZero) { //end of recursion
        return 0;
    }
    
    Reading newReading;
    newReading.size = 0;
    
    for (int i = 0; i < reading.size - 1; i++) {
        newReading.values[i] = reading.values[i + 1] - reading.values[i];
        newReading.size++;
    }

    return reading.values[newReading.size] + recursionSum(newReading);
}

Reading reverse( Reading reading ) {
    Reading newReading;
    newReading.size = 0;

    for (int i = reading.size - 1; i >= 0; i--) {
        newReading.values[newReading.size] = reading.values[i];
        newReading.size++;
    }

    return newReading;
}

int main(void) {
    FILE* fp;

#if SAMPLE == 1
    fp = fopen("sample.txt", "r");
#else
    fp = fopen("input.txt", "r");
#endif

    if (fp == NULL) {
        perror("error opening file");
        return(-1);
    }

    Readings readings;
    readings.size = 0;
    char line[512];

    while (fgets(line, 512, fp) != NULL) {
        Reading reading;
        reading.size = 0;

        char* token = strtok(line, " ");
        while (token != NULL) {
            reading.values[reading.size] = atol(token);
            reading.size++;
            token = strtok(NULL, " ");
        }

        readings.readings[readings.size] = reading;
        readings.size++;
    }

    fclose(fp);

    /*
     * PART 1, GENERATE PREDICTED VALUES AND SUM THEM
     */
    long sum = 0;
    for (int i = 0; i < readings.size; i++) {
        sum += recursionSum(readings.readings[i]);
    }
    
    printf("Sum part 1: %ld\n", sum);

    /**
     * PART 2, REVERSE THE ARRAY FIRST ANDD THEN SUM
    */

    for (int i = 0; i < readings.size; i++) {
        readings.readings[i] = reverse(readings.readings[i]);
    }


    sum = 0;
    for (int i = 0; i < readings.size; i++) {
        sum += recursionSum(readings.readings[i]);
    }

    printf("Sum part 2: %ld\n", sum);

    return 0;
}