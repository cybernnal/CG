//
// Created by tom on 14/10/16.
//

#include "cg.h"

static void     init_ia(t_ia *ia)
{
    ia->p_3_1 = 0 | TOP | LEFT | RIGHT;
    ia->p_3_2 = 0 | BOT | LEFT | RIGHT;
    ia->p_3_3 = 0 | TOP | BOT | LEFT;
    ia->p_3_4 = 0 | TOP | BOT | RIGHT;
}

static int      is_t_pos(int **map, int x, int y)
{
    if (map[y][x] & TOP && map[y][x] & LEFT && map[y][x] & RIGHT && !P_SET(map[y][x]))
        return (1);
    else if (map[y][x] & BOT && map[y][x] & LEFT && map[y][x] & RIGHT && !P_SET(map[y][x]))
        return (2);
    else if (map[y][x] & TOP && map[y][x] & LEFT && map[y][x] & BOT && !P_SET(map[y][x]))
        return (4);
    else if (map[y][x] & TOP && map[y][x] & BOT && map[y][x] & RIGHT && !P_SET(map[y][x]))
        return (3);
    else
        return (0);
}

static int      is_z_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (1);
    else
        return (0);
}


static int      is_tt_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (3);
    else if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !P_SET(map[y][x]))
        return (1);
    else if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (1);
    else if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (1);
    else if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (2);
    else if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (2);
    else
        return (0);
}

static int      is_o_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (4);
    else if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !P_SET(map[y][x]))
        return (3);
    else if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !P_SET(map[y][x]))
        return (1);
    else if (map[y][x] & USE_SET && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (2);
    else
        return (0);
}

static int      is_ob_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !P_SET(map[y][x]) && is_t_pos(map, x, y))
        return (4);
    else if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !P_SET(map[y][x]) && is_t_pos(map, x, y))
        return (3);
    else if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !P_SET(map[y][x]) && is_t_pos(map, x, y))
        return (1);
    else if (map[y][x] & USE_SET && !(map[y][x] & TOP) && !P_SET(map[y][x]) && is_t_pos(map, x, y))
        return (2);
    else
        return (0);
}

static int      step_one(t_env * env, t_pars *pars, t_ia *ia)
{
    int x;
    int y;

    x = 0;
    y = 0;
    pars->pos = 0;
    while(y < env->size)
    {
        while (x < env->size)
        {
            if ((pars->pos = is_t_pos(env->map, x, y)))
                break ;
            x++;
        }
        if (pars->pos != 0)
            break;
        y++;
        x = 0;
    }
    pars->x = x;
    pars->y = y;
    if (y == env->size)
        return (0);
    return (1);
}

static int      step_two(t_env * env, t_pars *pars, t_ia *ia)
{
    int x;
    int y;

    x = 0;
    y = 0;
    pars->pos = 0;
    while(y < env->size)
    {
        while (x < env->size)
        {
            if ((pars->pos = is_z_pos(env->map, x, y)))
                break ;
            x++;
        }
        if (pars->pos != 0)
            break;
        y++;
        x = 0;
    }
    pars->x = x;
    pars->y = y;
    if (y == env->size)
        return (0);
    return (1);
}

static int      step_three(t_env * env, t_pars *pars, t_ia *ia)
{
    int x;
    int y;

    x = 0;
    y = 0;
    pars->pos = 0;
    while(y < env->size)
    {
        while (x < env->size)
        {
            if ((pars->pos = is_t_pos(env->map, x, y)))
                break ;
            x++;
        }
        if (pars->pos != 0)
            break;
        y++;
        x = 0;
    }
    pars->x = x;
    pars->y = y;
    if (y == env->size)
        return (0);
    return (1);
}

static int      step_four(t_env * env, t_pars *pars, t_ia *ia)
{
    int x;
    int y;

    x = 0;
    y = 0;
    pars->pos = 0;
    while(y < env->size)
    {
        while (x < env->size)
        {
            if ((pars->pos = is_tt_pos(env->map, x, y)))
                break ;
            x++;
        }
        if (pars->pos != 0)
            break;
        y++;
        x = 0;
    }
    pars->x = x;
    pars->y = y;
    if (y == env->size)
        return (0);
    return (1);
}

static int      step_five(t_env * env, t_pars *pars, t_ia *ia)
{
    int x;
    int y;

    x = 0;
    y = 0;
    pars->pos = 0;
    while(y < env->size)
    {
        while (x < env->size)
        {
            if ((pars->pos = is_ob_pos(env->map, x, y)))
                break ;
            x++;
        }
        if (pars->pos != 0)
            break;
        y++;
        x = 0;
    }
    pars->x = x;
    pars->y = y;
    if (y == env->size)
        return (0);
    return (1);
}

static int step_six(t_env *env, t_pars *pars)
{
    int x;
    int y;

    x = 0;
    y = 0;
    pars->pos = 0;
    while(y < env->size)
    {
        while (x < env->size)
        {
            if ((pars->pos = is_o_pos(env->map, x, y)))
                break ;
            x++;
        }
        if (pars->pos != 0)
            break;
        y++;
        x = 0;
    }
    pars->x = x;
    pars->y = y;
    if (y == env->size)
        return (0);
    return (1);
}


int      ft_ia(t_env *env, t_pars *pars)
{
    static t_ia     ia;
    static int      last = 0;

    if (!ia.p_3_2)
        init_ia(&ia);
    if (step_one(env, pars, &ia))
        return (42);
    if (last <= 2 && step_two(env, pars, &ia) && (last = 2))
        return (42);
    if (last <= 3 && step_three(env, pars, &ia) && (last = 3))
        return (42);
    if (last <= 4 && step_four(env, pars, &ia) && (last = 4))
        return (42);
    if (last <= 5 && step_five(env, pars, &ia) && (last = 5))
        return (42);
    if (last <= 6 && step_six(env, pars) && (last = 6))
        return (42);
    return (0);
}