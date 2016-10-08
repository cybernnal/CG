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
    if (j < 1)// || buf[i++])
        return (0);
    pars->pos = ft_atoi(nb);
    return (1);
}

static void  pars_n_play(t_env *env)
{
    char    buf[128];
    int     is_good;
    t_pars  pars;

    is_good = 0;
    while (!is_good)
    {
        ft_putendl(USAGE);
        ft_bzero(buf, 128);
        ft_bzero(&pars, sizeof(t_pars));
        read(1, buf, 127);
        if (ft_strlen(buf) >= 126)
            ft_error("Game Over, input fatal error: EXIT");
        if ((ft_pars(buf, &pars)) == 0)
            ft_putendl("input error, try again");
        is_good = do_round(pars.x, pars.y, pars.pos, env);
    }
}

int     do_game(t_env * env)
{

    env->p = 1;
    while (env->p1 + env->p2 < ((env->size + 1) * (env->size / 2) + 1))
    {
        print_map(env->map, env->size);
        render(env);
        ft_putstr("player ");
        env->p == 1 ? ft_putnbr(1) : ft_putnbr(2);
        ft_putstr(", please enter your move. ");
        pars_n_play(env);
        env->p *= -1;
    }
}