#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXCHAR 1000
#define NOT_FOUND -1
#define PART1 0
#define PART2 !PART1
#define SAMPLE 0

typedef struct
{
    char *m_name;
    int m_value;
} Number;

Number g_numbers[9] = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9}
};

int extractIntFromString(char *str);
int extractIntAndStringFromString(char *str);
int main(void)
{
    FILE *l_fp;
    char l_str[MAXCHAR];
#if SAMPLE
    char *l_filename = "sample.txt";
#else
    char *l_filename = "input.txt";
#endif

    l_fp = fopen(l_filename, "r");
    if (l_fp == NULL)
    {
        printf("Could not open file %s", l_filename);
        return 1;
    }

    int l_sum = 0;
    while (fgets(l_str, MAXCHAR, l_fp) != NULL)
    {
#if PART1
        int l_num = extractIntFromString(str);
#elif PART2
        int l_num = extractIntAndStringFromString(l_str);
#endif
        printf("%d\n", l_num);
        if (l_num != -1)
        {
            l_sum += l_num;
        }
    }
    printf("%d\n", l_sum);
    fclose(l_fp);

    return 0;
}

int extractIntFromString(char *p_str)
{
    int l_first = -1;
    int l_last = -1;
    for (int l_i = 0; l_i < strlen(p_str); l_i++)
    {
        if (p_str[l_i] >= '0' && p_str[l_i] <= '9')
        {
            if (l_first == NOT_FOUND)
            {
                l_first = p_str[l_i] - '0';
                l_last = l_first;
            }
            else
            {
                l_last = p_str[l_i] - '0';
            }
        }
    }
    if (l_first != NOT_FOUND)
    {
        return l_first * 10 + l_last;
    }
    return NOT_FOUND;
}

int extractIntAndStringFromString(char *p_str)
{
    int l_first = -1;
    int l_last = -1;

    char *l_curr = NULL;

    for (int l_i = 0; l_i < strlen(p_str); l_i++)
    {
        // we deal with numbers
        if (p_str[l_i] >= '0' && p_str[l_i] <= '9')
        {
            if (l_first == -1)
            {
                l_first = p_str[l_i] - '0';
                l_last = l_first;
            }
            else
            {
                l_last = p_str[l_i] - '0';
            }
        }
        else
        { // we deal with chars
            l_curr = &p_str[l_i];
            int *l_currVal = l_first == -1 ? &l_first : &l_last;

            for (int j = 0; j < 9; j++)
            {
                if (strncmp(l_curr, g_numbers[j].m_name, strlen(g_numbers[j].m_name)) == 0)
                {
                    *l_currVal = g_numbers[j].m_value;
                    break;
                }
            }
        }
    }
    if (l_first != NOT_FOUND)
    {
        return l_first * 10 + l_last;
    }
    return NOT_FOUND;
}