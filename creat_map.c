#include "cg.h"
#include <stdio.h>

static int 	mal_map(t_env *env)
{
    int i;

    i = 0;
    if (env->size < 3 || env->size > 10000 || env->size % 2 != 1)
        ft_error("wrong size of map.\n enter an even number betwin 3 and 10001");
    if (!(env->map = (int**)ft_memalloc(sizeof(int*) * (env->size))))
        ft_error("Malloc error");
    while (i < env->size)
    {
        if (!(env->map[i] = (int*)ft_memalloc(sizeof(int) * (env->size))))
            ft_error("Malloc error");
        ft_memset(env->map[i], UN_SET, (size_t)env->size);
        i++;
    }
    return (1);
}

static void    init_map(t_env *env)
{
    int     set;
    int     setr;
    int     setl;
    int     x;
    int     x1;
    int     y;
    int     i;

    setr = TOP;
    setr |= RIGHT;
    setl = TOP;
    setl |= LEFT;
    i = 0;
    x = env->size / 2;
    y = 0;
    set = NUL_SET;
    while (y < env->size / 2)
    {
        x1 = x;
        env->map[y][x++] = setl;
        while ((x - x1) + 1 <= y + i)
        {
            env->map[y][x] = set;
        //    printf("x: %d, y: %d, case: %d\n", x, y, env->map[y][x]);
            x++;
        }
        env->map[y][x] |= setr;
        i++;
        y++;
        x = x1 - 1;
    }
    setr = 0 | BOT | RIGHT;
    setl = 0 | BOT | LEFT;
    while (y < env->size)
    {
        x1 = x;
        env->map[y][x++] = setl;
        while ((x - x1 + 1) <= y + i)
        {
            env->map[y][x] = set;
    //        printf("x: %d, y: %d, case: %d\n", x, y, env->map[y][x]);
            x++;
        }
        env->map[y][x] |= setr;
        i -= 3;
        y++;
        x = x1 + 1;
    }
}

int creat_map(t_env *env)
{
    if (env->size % 2 == 0)
        env->size++;
    mal_map(env);
    init_map(env);
}