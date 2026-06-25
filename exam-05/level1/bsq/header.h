#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>

typedef struct square
{
    int start_x;
    int start_y;
    int len;
    int volume;
} square;

typedef struct info
{
    char **map;
    int len;
    int hight;
    char empty;
    char obstacle;
    char full;
} info;