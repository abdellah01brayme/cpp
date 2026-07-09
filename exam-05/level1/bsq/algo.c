#include "header.h"

void setsquer(square *s, square *src)
{
    if (!src)
    {
        s->len = 0;
        s->start_x = 0;
        s->start_y = 0;
    }
    else
    {
        s->len = src->len;
        s->start_x = src->start_x;
        s->start_y = src->start_y;
    }
}
int get_len(info *map, int y, int x)
{
    int lenx = 0;

    while (map->map[y][x + lenx] == map->empty)
        lenx++;
    int leny = 0;
    while (map->map[y + leny] && map->map[y + leny][x] == map->empty)
        leny++;
    int len;
    if (lenx < leny)
        len = lenx;
    else
        len = leny;
    int i = 0, j = 0;
    while (i < len)
    {
        j = 0;
        while (j < len)
        {
            if (map->map[y + i][x + j] != map->empty)
                len = j ;
            j++;
        }
        i++;
        if (!map->map[y + i] || map->map[y + i][x] != map->empty)
        {
            len = i ;
        }
    }
    printf("%d\n", len);
    return len;
}
square algo(info *map)
{
    square s,tmp;
    setsquer(&s, NULL);
    int x = 0;
    int y = 0;
    while (map->map[y])
    {
        x = 0;
        while (map->map[y][x])
        {
            int len = get_len(map, y, x);
            tmp.len = len;
            tmp.start_x = x;
            tmp.start_y = y;
            if (tmp.len > s.len)
                setsquer(&s, &tmp);
            x++;
        }
        y++;
    }
    return s;
}