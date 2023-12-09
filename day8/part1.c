#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

#define SAMPLE 0

#define NUM_LETTERS ('Z'-'A' + 1)
#define SIZEOFINSTRUCTIONS ( SAMPLE ? 2 : 293)

typedef struct {
    char name[4];
    int left;
    int right;
} Node;

int name_to_index( char* name ) {
    return (name[0]-'A') * NUM_LETTERS * NUM_LETTERS + (name[1]-'A') * NUM_LETTERS + (name[2]-'A');
}


Node nodes[ NUM_LETTERS*NUM_LETTERS*NUM_LETTERS] = {0};

int main() {
    char instructions[SIZEOFINSTRUCTIONS];

#if SAMPLE == 0
    FILE* f = fopen("input.txt", "r");
#else
    FILE* f = fopen("sample.txt", "r");
#endif

    //read first line in instructions
    fscanf(f, "%s", instructions);
    printf("Instructions: %s\n", instructions);
    char line[512];

    // skip line
    fgets(line, 256, f);

    //read all nodes
    while (fgets(line, 256, f) != NULL) {
        if (line[0] == '\n') { // skip empty lines
            continue;
        }
        Node node = {" ", name_to_index(&line[7]), name_to_index( &line[12])};
        strncpy((char *) &node.name, line, 3);
        node.name[3] = 0;
        nodes[name_to_index(&line[0])] = node;
    }

    int current = name_to_index("AAA");
    int end = name_to_index("ZZZ");

    int steps = 0;

    while (current != end) {
        if (instructions[steps % SIZEOFINSTRUCTIONS] == 'L') {
            current = nodes[current].left;
        } else {
            current = nodes[current].right;
        }
        steps++;
    }

    printf("Steps: %d\n", steps);
    
    fclose(f);

    return 0;
}