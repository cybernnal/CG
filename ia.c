//
// Created by tom on 14/10/16.
//

#include "cg.h"

static int      is_ok_pos(int **map, int x, int y)
{
    if (!(map[y][x] & TOP) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (1);
    else if (!(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (2);
    else if (!(map[y][x] & TOP) && !(map[y][x] & LEFT) && !(map[y][x] & BOT) && !P_SET(map[y][x]))
        return (4);
    else if (!(map[y][x] & TOP) && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (3);
    else
        return (0);
}

static int      is_th_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
    {
        if (is_ok_pos(map, x, y - 1))
            return (2);
        if (is_ok_pos(map, x + 1, y))
            return (4);
        if (is_ok_pos(map, x - 1, y))
            return (3);
    }
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
    {
        if (is_ok_pos(map, x, y + 1))
            return (1);
        if (is_ok_pos(map, x + 1, y))
            return (4);
        if (is_ok_pos(map, x - 1, y))
            return (3);
    }
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
    {
        if (is_ok_pos(map, x, y - 1))
            return (2);
        if (is_ok_pos(map, x, y + 1))
            return (1);
        if (is_ok_pos(map, x - 1, y))
            return (3);
    }
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
    {
        if (is_ok_pos(map, x, y - 1))
            return (2);
        if (is_ok_pos(map, x + 1, y))
            return (4);
        if (is_ok_pos(map, x, y + 1))
            return (1);
    }
    return (0);
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
        if (is_ok_pos(map, x, y + 1))
            return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x, y - 1))
            return (2);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x - 1, y))
            return (3);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x + 1, y))
            return (4);
    return (0);
}


static int      is_tt_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x + 1, y) && is_ok_pos(map, x - 1, y))
            return (4);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x, y + 1) && is_ok_pos(map, x - 1, y))
            return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x + 1, y) &&  is_ok_pos(map, x, y + 1))
            return (4);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x, y + 1) && is_ok_pos(map, x, y - 1))
            return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x, y - 1) && is_ok_pos(map, x - 1, y))
            return (2);
    if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        if (is_ok_pos(map, x + 1, y) && is_ok_pos(map, x, y - 1))
            return (4);
    return (0);
}

static int      is_last_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (4);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !P_SET(map[y][x]))
        return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (4);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (2);
    if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (4);
    return (0);
}

static int      is_ttt_pos(int **map, int x, int y)
{
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (4);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !P_SET(map[y][x]))
        return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
        return (4);
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (1);
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (2);
    if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
        return (4);
    return (0);
}

/*
 * last:
 * 1: last op = y + 1
 * 2: last op = y - 1
 * 3: last op = x - 1
 * 4: last op = x + 1
 */

static int      is_rec_pos(t_ia * ia, int **map, int x, int y, int max, int i, int last)
{
    printf("x: %d, y: %d, x0: %d, y0: %d, max: %d, i: %d, last: %d\n", x, y, ia->x0, ia->y0, max, i, last);
   if (i != 0 && x == ia->x0 && y == ia->y0)
        return (1);
    if (i >= max)
        return (0);
    if (is_t_pos(map, x, y))
        return (0);
    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
    {
        if (i != 0 && is_ok_pos(map, x + 1, y) && last != 4)
            return (4);
        if  (i != 0 && is_ok_pos(map, x - 1, y) && last != 3)
            return (3);
        if (last != 3 && is_rec_pos(ia, map, x - 1, y, max, i + 1, 4) && (i != 0 || (last != 4 && is_rec_pos(ia, map, x + 1, y, max, i + 1, 3))))
            return (3);
        if (last != 4 && is_rec_pos(ia, map, x + 1, y, max, i + 1, 3) && (i != 0 || (last != 3 && is_rec_pos(ia, map, x - 1, y, max, i + 1, 4))))
            return (4);
    }
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & LEFT) && !P_SET(map[y][x]))
    {
        if (i != 0 && is_ok_pos(map, x, y + 1) && last != 1)
            return (1);
        if (i != 0 && is_ok_pos(map, x - 1, y) && last != 3)
            return (3);
        if (last != 3 && is_rec_pos(ia, map, x - 1, y, max, i + 1, 4) && (i != 0 || (last != 1 && is_rec_pos(ia, map, x, y + 1, max, i + 1, 2))))
            return (3);
        if (last != 1 && is_rec_pos(ia, map, x, y + 1, max, i + 1, 2) && (i != 0 || (last != 3 && is_rec_pos(ia, map, x - 1, y, max, i + 1, 4))))
            return (1);
    }
    if (i != 0 && map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & RIGHT) && !P_SET(map[y][x]))
    {
        if (i != 0 && is_ok_pos(map, x, y + 1) && last != 1)
            return (1);
        if (i != 0 && is_ok_pos(map, x + 1, y) && last != 4)
            return (4);
        if (last != 4 && is_rec_pos(ia, map, x + 1, y, max, i + 1, 3) && (i != 0 || (last != 1 && is_rec_pos(ia, map, x, y + 1, max, i + 1, 2))))
            return (4);
        if (last != 1 && is_rec_pos(ia, map, x, y + 1, max, i + 1, 2) && (i != 0 || (last != 4 && is_rec_pos(ia, map, x + 1, y, max, i + 1, 3))))
            return (1);
    }
    if (map[y][x] & USE_SET && !(map[y][x] & BOT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
    {
        if (i != 0 && is_ok_pos(map, x, y + 1) && last != 1)
            return (1);
        if (i != 0 && is_ok_pos(map, x, y - 1) && last != 2)
            return (2);
        if (last != 2 && is_rec_pos(ia, map, x, y - 1, max, i + 1, 1) && (i != 0 || (last != 1 && is_rec_pos(ia, map, x, y + 1, max, i + 1, 2))))
            return (2);
        if (last != 1 && is_rec_pos(ia, map, x, y + 1, max, i + 1, 2) && (i != 0 || (last != 2 && is_rec_pos(ia, map, x, y - 1, max, i + 1, 1))))
            return (1);
    }

    if (map[y][x] & USE_SET && !(map[y][x] & LEFT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
    {
        if (i != 0 && is_ok_pos(map, x, y - 1) && last != 2)
            return (2);
        if (i != 0 && is_ok_pos(map, x - 1, y) && last != 3)
            return (3);
        if (last != 3 && is_rec_pos(ia, map, x - 1, y, max, i + 1, 4) && (i != 0 || (last != 2 && is_rec_pos(ia, map, x, y - 1, max, i + 1, 1))))
            return (3);
        if (last != 2 && is_rec_pos(ia, map, x, y - 1, max, i + 1, 1) && (i != 0 || (last != 3 && is_rec_pos(ia, map, x - 1, y, max, i + 1, 4))))
            return (2);
    }
    if (map[y][x] & USE_SET && !(map[y][x] & RIGHT) && !(map[y][x] & TOP) && !P_SET(map[y][x]))
    {
        if (i != 0 && is_ok_pos(map, x, y - 1) && last != 2)
            return (2);
        if (i != 0 && is_ok_pos(map, x + 1, y) && last != 4)
            return (4);
        if (last != 4 && is_rec_pos(ia, map, x + 1, y, max, i + 1, 3) && (i != 0 || (last != 2 && is_rec_pos(ia, map, x, y - 1, max, i + 1, 1))))
            return (4);
        if (last != 2 && is_rec_pos(ia, map, x, y - 1, max, i + 1, 1) && (i != 0 || (last != 4 && is_rec_pos(ia, map, x + 1, y, max, i + 1, 3))))
            return (2);
    }
    return (0);
}


static int      step_one(t_env * env, t_pars *pars)
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

static int      step_two(t_env * env, t_pars *pars)
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

static int      step_three(t_env * env, t_pars *pars)
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
            if ((pars->pos = is_th_pos(env->map, x, y)))
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

static int      step_four(t_env * env, t_pars *pars)
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
    int max;

    max = 1;
    pars->pos = 0;
    while (max < env->size)
    {
        x = 0;
        y = 0;
        while(y < env->size)
        {
            while (x < env->size)
            {
                ia->y0 = y;
                ia->x0 = x;
                if ((pars->pos = is_rec_pos(ia, env->map, x, y, max, 0, 0)))
                    break ;
                x++;
            }
            if (pars->pos != 0)
                break;
            y++;
            x = 0;
        }
        if (pars->pos != 0)
            break;
        max++;
    }
    if (y == env->size)
        return (0);
    pars->x = x;
    pars->y = y;
    return (1);
}

static int      step_last(t_env * env, t_pars *pars)
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
            if ((pars->pos = is_last_pos(env->map, x, y)))
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

    if (step_one(env, pars))
        return (42);
    if (last <= 2 && step_two(env, pars) && (last = 2))
        return (43);
    if (last <= 3 && step_three(env, pars) && (last = 3))
        return (44);
    if (last <= 4 && step_four(env, pars) && (last = 4))
        return (45);
    if (last <= 5 && step_five(env, pars, &ia) && (last = 5))
        return (46);
    if (step_last(env, pars))
        return (47);
    return (0);
}