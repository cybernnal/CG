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
    int     x;
    int     x1;
    int     y;
    int     i;

    i = 0;
    x = env->size / 2;
    y = 0;
    while (y < env->size / 2)
    {
        x1 = x;
        put_masque(x, y, TOP, env);
        put_masque(x, y, LEFT, env);
        if (y != 0)
            x++;
        while ((x - x1) + 1 <= y + i)
        {
            put_masque(x, y, NUL_SET, env);
            x++;
        }
        put_masque(x, y, TOP, env);
        put_masque(x, y, RIGHT, env);
        i++;
        y++;
        x = x1 - 1;
    }
    put_masque(x, y, TOP, env);
    while (y < env->size)
    {
        x1 = x;
        if (y != env->size - 1)
            put_masque(x, y, BOT, env);
        put_masque(x, y, LEFT, env);
        if (y != env->size - 1)
            x++;
        while ((x - x1 + 1) <= y + i)
        {
            put_masque(x, y, NUL_SET, env);
            x++;
        }
        put_masque(x, y, BOT, env);
        put_masque(x, y, RIGHT, env);
        if (y == env->size / 2)
            put_masque(x, y, TOP, env);
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