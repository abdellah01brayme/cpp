#include "header.h"

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
    if (buf[*i]) return 1;
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
