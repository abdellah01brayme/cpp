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
void setinfo(info *s)
{
    s->empty = 0;
    s->full = 0;
    s->len = 0;
    s->hight = 0;
    s->map = 0;
    s->obstacle = 0;
}

int map_err(int err)
{
    if (err)
        fprintf(stderr, "%s\n", strerror(errno));
    else
        fprintf(stderr, "map error\n");
    return 1;
}
void free_map(info *map, int len)
{
    int i = 0;
    while (i < len)
    {
        free(map->map[i]);
        i++;
    }
    free (map->map);
}
int check_inf(char *buf, int *i, char *c)
{
    if (buf[*i] != ' ') return 1;
    (*i)++;
    if (!buf[*i]) return 1;
    *c = buf[*i];
    (*i)++;
    return 0;
}
int map_info(FILE *f, info *map)
{
    size_t size = 0;
    char *buf = 0;

    int len = getline(&buf, &size, f);
    if (len < 0)
        return (map_err(1));
    else if (buf[len - 1] != '\n')
        return free(buf), map_err(0);
    int n = 0, i = 0;
    if (buf[0] < '0' || buf[0] > '9')
        return free(buf), map_err(0);
    while (!(buf[i] < '0' || buf[i] > '9'))
    {
        n = n * 10 + buf[i] - '0';
        i++;
    }
    map->hight = n;
    if (check_inf(buf, &i, &map->empty))
        return free(buf), map_err(0);
    if (check_inf(buf, &i, &map->obstacle))
        return free(buf), map_err(0);
    if (check_inf(buf, &i, &map->full))
        return free(buf), map_err(0);
    if (buf[i] != '\n')
        return free(buf), map_err(0);
    free (buf);
    
    return 0;       
}
int valide_line(info *map, int i)
{
    int j = 0;
    while (map->map[i][j])
    {
        if (map->map[i][j] != map->empty && map->map[i][j] != map->obstacle && map->map[i][j] != map->full)
            return 1;
        j++;
    }
    if (!j)
        return 1;
    return 0;
}
int read_map(FILE *file, info *map)
{
    setinfo(map);
    if (map_info(file, map))
        return 1;
    map->map = malloc ((map->hight + 1) * sizeof(char *));
    if (!map->map)
        return map_err(1);
    
    int i = 0;
    size_t size = 0;
    ssize_t len;
    while (i < map->hight)
    {
        map->map[i] = NULL;
        len = getline(&map->map[i], &size, file);
        if (len < 0)
        {
            if (errno)
                return free_map(map, i), map_err(1);
            if (size)
                free(map->map[i]);
            break;
        }
        else if (!len)
            break;
        else if (map->map[i][len -1] != '\n')
            return free_map(map, i), map_err(0);
        map->map[i][len -1] = '\0';
        if (i == 0)
        {
            map->len = len;
            if (!len || !map->hight)
                return free_map(map, i), map_err(0);
        }
        if (len != map->len || valide_line(map, i))
            return free_map(map, i), map_err(0);
        i++;
    }
    map->map[i] = NULL;
    return 0;
}
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