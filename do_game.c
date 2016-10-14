#include <sys/termios.h>
#include "cg.h"

/*
 * dirty for no malloc
 */

static int   ft_pars(char *buf, t_pars *pars)
{
    char    nb[11];
    int     i;
    int j;

    j = 0;
    i = 0;
    ft_bzero(nb, 11);
    while (ft_isdigit(buf[i]))
    {
        nb[i] = buf[i];
        i++;
    }
    if (i++ < 1)
        return (0);
    pars->x = ft_atoi(nb);
    ft_bzero(nb, 11);
    while (ft_isdigit(buf[i]))
        nb[j++] = buf[i++];
    if (j < 1)
        return (0);
    pars->y = ft_atoi(nb);
    j = 0;
    i++;
    ft_bzero(nb, 11);
    while (ft_isdigit(buf[i]))
        nb[j++] = buf[i++];
    if (j  < 1)
        return (0);
    pars->pos = ft_atoi(nb);
    return (1);
}

static int kbhit()
{
    struct timeval tv;
    fd_set fds;
    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

static unsigned int     get_pos(float x, float y)
{
    if (y < 0.25 && x < 1 - y && x > y)
        return (2);
    else if (y > 1 - 0.25 && x > 1 - y && x < y)
        return (1);
    else if (x < 0.25 && y < 1 - x && y > x)
        return (3);
    else if (x > 1 - 0.25 && y > 1 - x && y < x)
        return (4);
    else
        return (0);
}

static void     get_mouse_coor(int x, int y, t_pars *pars, t_env *env)
{
    static int len = 0;
    static int marx;
    static int mary;
    float       xx;
    float       yy;

    if (!len)
    {
        len = ((WIN_HEIGHT - MAR * 2)) / env->size;
        marx = (WIN_WIDTH - (len * env->size)) / 2;
        mary = (WIN_HEIGHT - (len * env->size)) / 2;
    }
    pars->xm = (float)(x - marx) / len;
    pars->ym = (float)(y - mary) / len;
    xx = pars->xm - (int)pars->xm;
    yy = pars->ym - (int)pars->ym;
    pars->x = (int)pars->xm;
    pars->y = (int)pars->ym;
    pars->pos = get_pos(xx, yy);
}

static int      mouse_hit(t_pars *pars, t_env *env)
{
    int x;
    int y;

    x = 0;
    y = 0;
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        get_mouse_coor(x, y, pars, env);
        usleep(100000);
        return (42);
    }
    return (0);
}

static void  pars_n_play(t_env *env)
{
    int     is_good;
    t_pars  pars;
    int        i;

    is_good = 0;
    while (!is_good)
    {
        ft_putendl(USAGE);
        ft_bzero(&pars, sizeof(t_pars));
        i = 0;
        if ((env->ia == 1 && env->p == -1) || (env->ia == 2))
            i = ft_ia(env, &pars);
        while (i == 0)
        {
            render(env);
            i = kbhit();
            if (i != 0)
                read(1, pars.buf, 127);
            if (i == 0)
                i = mouse_hit(&pars, env);
        }
        if (i != 42)
        {
            if (!ft_strcmp(pars.buf, "quit\n"))
                exit(0);
            if (ft_strlen(pars.buf) >= 126)
                ft_error("Game Over, input fatal error: EXIT");
            if ((ft_pars(pars.buf, &pars)) == 0)
            {
                ft_putendl("input error, try again");
                continue;
            }
        }
        is_good = do_round(pars.x, pars.y, pars.pos, env);
        if (env->ret == 1)
        {
            if (env->p1 + env->p2 >= ((env->size + 1) * (env->size / 2) + 1))
                exit (1);
            print_map(env->map, env->size);
            ft_putendl("gg you earn a point, please replay");
            render(env);
            is_good = 0;
            env->ret = 0;
        }
    }
}

int     do_game(t_env * env)
{
    env->p = 1;
    while (env->p1 + env->p2 < ((env->size + 1) * (env->size / 2) + 1))
    {
        render(env);
        print_map(env->map, env->size);
        ft_putstr("player ");
        env->p == 1 ? ft_putnbr(1) : ft_putnbr(2);
        ft_putendl(", please enter your move. ");
        pars_n_play(env);
        env->p *= -1;
    }
}