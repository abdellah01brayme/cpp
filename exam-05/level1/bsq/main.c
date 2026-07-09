#include "header.h"

void draw_square(info *map, square *s)
{
    
    int y = s->start_y;
    while (y < s->start_y + s->len)
    {
        int x = s->start_x;
        while (x < s->start_x + s->len)
        {
            map->map[y][x] = map->full;
            x++;
        }
        y++;
    }
}
int main(int ac, char **av)
{
    info map;
    FILE *file;
    if (ac > 2)
    {
        fprintf(stderr, "map error\n");
        return 1;
    }
    if (ac == 1)
        file = fopen("/dev/stdin", "r");
    else
        file = fopen(av[1], "r");
    if (!file)
    {
        fprintf(stderr, "map error\n");
        return 1;
    }
    if (read_map(file, &map))
        return (fclose(file), 1);
    fprintf(stdin, "all right\n");
    int i = 0;
    square s = algo(&map);
    // s.start_x = 5;
    // s.start_y = 0;
    // s.len = 7;
    draw_square(&map, &s);
    while (map.map[i])
        printf("%s\n", map.map[i++]);
    free_map(&map, map.hight);
    fclose(file);
    return 0;
}