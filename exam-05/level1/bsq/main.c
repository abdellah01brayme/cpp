#include "header.h"

int check_inf(char *buf, int *i, char *c)
{
    if (buf[*i] == ' ') (*i)++;
    else return 1;
    if (!buf[*i]) return 1;
    *c = buf[*i];
    return 0;
}
int map_info(FILE *f, info *map)
{
    size_t size = 0;
    char *buf = 0;

    ssize_t n = getline(&buf, &size, f);
    if (n < 0)
        return 1;
    if (buf[n - 1] != '\n')
        return free(buf), 1;
    if (buf[0] < '0' || buf[0] > '9')
        return free(buf), 1;
    int i = 0;
    while (buf[i] >= '0' && buf[i] <= '9')
        map->hight += 10 * (buf[i++] - '0');
    if (check_inf(buf, &i, map->empty) || check_inf(buf, &i, map->obstacle) || check_inf(buf, &i, map->full))
        return free(buf), 1;
    if (buf[i] != '\n')
        return free(buf), 1;
    free(buf);
    if (map->empty != map->full != map->obstacle)
        return 1;
    return 0;       
}

int read_map(FILE *file, info *map)
{
    char *tmp;
    if (map_info(file, map))
        return 1;
}
void setsquer(square *s)
{
    s->len = 0;
    s->start_x = 0;
    s->start_y = 0;
    s->volume = 0;
}
void setinfo(info *s)
{
    s->empty = 0;
    s->full = 0;
    s->len = 0;
    s->hight = 0;
    s->map = 0;
    s->obstacle = 0;
}
int main(int ac, char **av)
{
    info map;
    setinfo(&map);
    FILE *file;
    FILE *ferr;
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
    fclose(file);
    return 0;
}