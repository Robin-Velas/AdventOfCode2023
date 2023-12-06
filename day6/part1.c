#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define SAMPLE 1
#define NBINPUT (SAMPLE ? 3 : 4)

int calculate(int time, int record) {
    int nbWaysToBeatRecord = 0;
    for (int i = 0; i < time; i++) {
        int remainingTime = time - i;
        // i = speed
        int distance = i * remainingTime;
        if (distance > record) {
            nbWaysToBeatRecord++;
        }
    }
    return nbWaysToBeatRecord;
}

int main() {
    char name[512];
    long arrayTime[NBINPUT];
    long arrayRecord[NBINPUT];
#if SAMPLE == 0
    FILE* f = fopen("input.txt", "r");
#else
    FILE* f = fopen("sample.txt", "r");
#endif
    //ignore time
    fscanf(f, "Time:");
    //scan 3 times in %d %d %d
    for (int i = 0; i < NBINPUT; i++) {
        fscanf(f, "%d", &arrayTime[i]);
    }

    //ignore record
    fscanf(f, "\nDistance:");
    for (int i = 0; i < NBINPUT; i++) {
        fscanf(f, "%d", &arrayRecord[i]);
    }
    
    long result = 1;

    //time & record
    for (int i = 0; i < NBINPUT; i++) {
        result *= calculate(arrayTime[i], arrayRecord[i]);
    }
    printf("%d", result);

    return 0;
}