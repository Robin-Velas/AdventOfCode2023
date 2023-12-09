#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define SAMPLE 0
#define NBINPUT (SAMPLE ? 5 : 1000)
#define NBCARDS 5

typedef struct {
    char cards[NBCARDS];
    int value;
    int type;
} Hand;

int convertCard(char card) {
    switch (card) {
        case 'J': //jocker, no value
            return -1;
        case 'A':
            return 14;
        case 'K':
            return 13;
        case 'Q':
            return 12;
        case 'T':
            return 10;
        default:
            return card - '0';
    }
}

int cmpfunc(const void* a, const void* b) {
    return (*(int*)b - *(int*)a);
}

int comparaison(const void* a, const void* b) {
    Hand handA = *(Hand*)a;
    Hand handB = *(Hand*)b;
    if (handA.type > handB.type) {
        return 1;
    }
    if (handA.type < handB.type) {
        return -1;
    }
    for (int i = 0; i < NBCARDS; i++) {
        if (convertCard(handA.cards[i]) > convertCard(handB.cards[i])) {
            return 1;
        } else if (convertCard(handA.cards[i]) < convertCard(handB.cards[i])) {
            return -1;
        }
    }
    return 0;
}

void giveTypeToHands(Hand* hands) {
    for (int i = 0; i < NBINPUT; i++) {
        int array[15] = {0};

        for (int j = 0; j < NBCARDS; j++) {
            int card = convertCard(hands[i].cards[j]);
            array[card]++;
        }

        //Get nb of jockers out
        int nbJ = array[convertCard('J')];
        array[convertCard('J')] = 0;

        // Sort the array in descending order
        qsort(array, 15, sizeof(int), cmpfunc);

        //add jockers to array
        array[0] += nbJ;
     
        if (array[0] == 5) {
            hands[i].type = 7;
        } else if (array[0] == 4) {
            hands[i].type = 6;
        } else if (array[0] == 3 && array[1] == 2) {
            hands[i].type = 5;
        } else if (array[0] == 3) {
            hands[i].type = 4;
        } else if (array[0] == 2 && array[1] == 2) {
            hands[i].type = 3;
        } else if (array[0] == 2) {
            hands[i].type = 2;
        } else if (array[0] == 1) {
            hands[i].type = 1;
        }
    }
}

int main() {
    Hand hands[NBINPUT]; 
#if SAMPLE == 0
    FILE* f = fopen("input.txt", "r");
#else
    FILE* f = fopen("sample.txt", "r");
#endif

    for (int i = 0; i < NBINPUT; i++) {
        fscanf(f, "%s %d", hands[i].cards, &hands[i].value);
    }

    fclose(f);
    
    giveTypeToHands(hands);

    qsort(hands, NBINPUT, sizeof(Hand), comparaison);

    //DEBUG: print all
    for (int i = 0; i < NBINPUT; i++) {
        printf("%s %d %d rank:%d\n", hands[i].cards, hands[i].value, hands[i].type, (i + 1) );
    }

    long sum = 0;
    for (int i = 0; i < NBINPUT; i++) {
        int result = hands[i].value * (i + 1);
        sum += result;
    }

    printf("%ld\n", sum);

    return 0;
}