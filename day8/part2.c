#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <inttypes.h>

#define SAMPLE 0

#define NUM_LETTERS ('Z' - 'A' + 1)
#define SIZEOFINSTRUCTIONS (SAMPLE ? 2 : 293)

typedef struct
{
    char name[4];
    int left;
    int right;
} Node;

Node nodes[NUM_LETTERS * NUM_LETTERS * NUM_LETTERS] = {0};

int name_to_index(char *name)
{
    return (name[0] - 'A') * NUM_LETTERS * NUM_LETTERS + (name[1] - 'A') * NUM_LETTERS + (name[2] - 'A');
}

uint64_t find_lcm( uint64_t a, uint64_t b ) {
    uint64_t current[ 2 ] = {0};
    for( ;; ) {
        if( current[0] < current[1] ) {
            current[0] += a;
        } else {
            current[1] += b;
        }
        if( current[0] == current[1]) return current[0];
    }
}

int find_loops( char* start, char* instructions ) {
    int current_loc = name_to_index(start);
    char *current_instruction = instructions;
    int num_steps = 0;
    for(;;) {
        // The puzzle is initially tried to solve. On reaching the xxZ node the chain loops back to the start. Neither
        // looping back to start or looping back to the start of the chain is given but the puzzle seems to guarantee it
        if( nodes[ current_loc ].name[2] == 'Z' ) {
            return num_steps;
        }
        current_loc = *current_instruction++ == 'L' ? nodes[ current_loc].left : nodes[ current_loc].right;
        if( *current_instruction != 'L' && *current_instruction != 'R') current_instruction = instructions;
        num_steps ++;
    };
}


int main()
{
    char instructions[SIZEOFINSTRUCTIONS];
    char StartNames[512][4]; // will be less than 512

#if SAMPLE == 0
    FILE *f = fopen("input.txt", "r");
#else
    FILE *f = fopen("sample.txt", "r");
#endif

    // read first line in instructions
    fscanf(f, "%s", instructions);
    char line[512];

    // skip line
    fgets(line, 256, f);

    int numStartNames = 0;
    // read all nodes
    while (fgets(line, 256, f) != NULL)
    {
        if (line[0] == '\n')
        { // skip empty lines
            continue;
        }
        Node node = {" ", name_to_index(&line[7]), name_to_index(&line[12])};
        strncpy((char *)&node.name, line, 3);
        node.name[3] = 0;
        nodes[name_to_index(&line[0])] = node;

        if (node.name[2] == 'A')
        {
            memcpy(StartNames[numStartNames], node.name, 4);
            numStartNames++;
        }
    }

    fclose(f);

    int current[numStartNames];
    for (int i = 0; i < numStartNames; i++)
    {
        current[i] = name_to_index(StartNames[i]);
    }

    //print all nodes numStartNames
    // for (int i = 0; i < numStartNames; i++)
    // {
    //     printf("Current %d  name: %s\n", i, nodes[current[i]].name);
    // }

    uint64_t  lcm =1 ;
    for (int i = 0; i < numStartNames; i++)
    {
        uint64_t  loop_size = find_loops( StartNames[ i ], instructions );
        lcm = find_lcm( lcm, loop_size);
    }

    printf("Steps: %" PRIu64 "\n", lcm);

    return 0;
}