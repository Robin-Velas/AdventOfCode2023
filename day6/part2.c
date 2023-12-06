#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

long long calculate(long long time, long long record) {
    long long nbWaysToBeatRecord = 0;
    for (long long i = 0; i < time; i++) {
        long long remainingTime = time - i;
        // i = speed
        long long distance = i * remainingTime;
        if (distance > record) {
            nbWaysToBeatRecord++;
        }
    }
    return nbWaysToBeatRecord;
}
int main()
{
    
    long long time = 58996469;
    long long distance = 478223210191071;
    //printf("Time: %d, record: %d\n", time, distance);
    long long result = calculate(time, distance);
   
    printf("%d", result);

    return 0;
}