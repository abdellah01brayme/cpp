#include <stdio.h>
#include <stdbool.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

typedef struct square
{
    int start_x;
    int start_y;
    int len;
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


int read_map(FILE *file, info *map);
void free_map(info *map, int len);
int map_err(int err);

square algo(info *map);