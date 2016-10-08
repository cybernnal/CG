#include "cg.h"

static unsigned int     ret_pos(int p)
{
    if (p == 1)
        return (BOT);
    else if (p == 2)
        return (TOP);
    else if (p == 3)
        return (LEFT);
    else if (p == 4)
        return (RIGHT);
    else
        return (0);
}

static unsigned int     ret_not_pos(int p)
{
    if (p == BOT)
        return (TOP);
    else if (p == TOP)
        return (BOT);
    else if (p == RIGHT)
        return (LEFT);
    else if (p == LEFT)
        return (RIGHT);
    else
        return (0);
}
static void     put_in(int x, int y, unsigned int pos, t_env *env)
{
    env->map[y][x] |= pos;
    if (env->map[y][x] & SET)
        set_point(env, x, y);
    if (pos == BOT)
        y++;
    else if (pos == TOP)
        y--;
    else if (pos == LEFT)
        x--;
    else if (pos == RIGHT)
        x++;
    pos = ret_not_pos(pos);
    if (pos == 0 || env->map[y][x] == UN_SET ||
        env->map[y][x] & P_ONE_SET || env->map[y][x] & P_TWO_SET || env->map[y][x] & pos)
    {
        ft_putendl("you lose a round :p");
        return ;
    }
    env->map[y][x] |= pos;
    if (env->map[y][x] & SET)
        set_point(env, x, y);
}

int    do_round(int x, int y, int p, t_env *env)
{
    unsigned int    pos;
    int             size;

    size = env->size - 1;
    pos = ret_pos(p);
    if (pos == 0 || x < 0 || x > size || y < 0 ||
            y > size || env->map[y][x] == UN_SET ||
            env->map[y][x] & P_ONE_SET || env->map[y][x] & P_TWO_SET || env->map[y][x] & pos)
    {
        ft_putstr("error input ");
        return (0);
    }
    put_in(x, y, pos, env);
    return (1);
}