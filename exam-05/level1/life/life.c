 #include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
typedef struct life
{
    char **arr;
    int x;
    int y;
    int w;
    int h;
    int iter;
    int draw;
} life;

void freearr(char ***arr)
{
    int i =0;
    while ((*arr)[i])
    {
        free((*arr)[i]);
        i++;
    }
    free((*arr));
    *arr = NULL;
}
char **set(life *l)
{
    int i = 0;
    char **arr = malloc((l->h + 1) * sizeof(char*));
    if (!arr)
        return NULL;
    while (i <= l->h)
    {
        arr[i] = NULL;
        i++;
    }
    i = 0;
    while (i < l->h)
    {
        arr[i] = malloc((l->w + 1) * sizeof(char));
        if (!arr[i])
        {
            freearr(&arr);
            return NULL;
        }
        int j = 0;
        while (j < l->w)
            arr[i][j++] = ' ';
        arr[i][j] = 0;
        i++;
    }
    return arr;
}
int live (life *l, int i, int j)
{
    if (i < 0 || j < 0)
        return 0;
    else if (i >= l->w || j >= l->h)
        return 0;
    if (l->arr[i][j] == '0')
        return 1;
    return 0;
}
int count (life *l, int i, int j)
{
    int n = 0;
    n += live(l, i - 1, j - 1);
    n += live(l, i - 1, j);
    n += live(l, i - 1, j + 1);

    n += live(l, i, j - 1);
    n += live(l, i, j + 1);

    n += live(l, i + 1, j - 1);
    n += live(l, i + 1, j);
    n += live(l, i + 1, j + 1);
    return n;
}

int iters(life *l)
{
    int i = 0;
    int n;
    char **cp = set(l);
    if (!cp)
        return 1;
    while (i < l->h)
    {
        int j = 0;
        while (j < l->w)
        {
            n = count(l, i, j);
            if (l->arr[i][j] == '0' && (n == 2 || n == 3))
                cp[i][j] = '0';
            else if (l->arr[i][j] != '0' && n == 3)
                cp[i][j] = '0';
            // printf ("%c %d %c (%d,%d)\n",l->arr[i][j], n, cp[i][j], i, j );
            j++;
        }
        i++;
    }
    freearr(&l->arr);
    l->arr = &cp[0];
    return 0;
}
int main(int ac, char **av)
{
    if (ac != 4)    
        return 1;
    life l;
    l.w = atoi(av[1]);
    l.h = atoi(av[2]);
    l.iter = atoi(av[3]);
    l.x = 0;
    l.draw = 0;
    l.y = 0;
    l.arr = set(&l);
    if (!l.arr)
        return 1;
    int size;
    char c;
    while (1)
    {
        if (l.draw)
            l.arr[l.y][l.x] = '0';
        size = read(0, &c, 1);
        if (!size)
            break;
        if (size < 0)
            return (freearr(&l.arr), 1);
        if (c == '\n')
            continue;
        if (c == 'w')
            l.y--;
        else if (c == 'a')
            l.x--;
        else if (c == 's')
            l.y++;
        else if (c == 'd')
            l.x++;
        else if (c == 'x')
            l.draw = !l.draw;
        else
            return (freearr(&l.arr), 1);
        if (l.x == l.w)
            l.x--;
        else if (l.x < 0)
            l.x = 0;
        if (l.y == l.h)
            l.y--;
        else if (l.y < 0)
            l.y = 0;
    }
    int i = 0;
    while (i < l.iter)
    {
        if (iters(&l))
            return freearr(&l.arr), 1;
        i++;
    }
    i = 0;
    while (i < l.h)
    {
        printf("%s\n", l.arr[i]);
        i++;
    }
    int n = 10;
    n << 10;
    printf("%d\n", n);
    freearr(&l.arr);
    return 0;
}