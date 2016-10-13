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
    FD_SET(STDIN_FILENO, &fds); //STDIN_FILENO is 0
    select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

static void     get_mouse_coor(int x, int y, t_pars *pars)
{

}

static int      mouse_hit(t_pars *pars, t_env *env)
{
    int x;
    int y;

    x = 0;
    y = 0;
    if (SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT))
    {
        SDL_Log("Mouse Button 1 (left) is pressed. %d %d\n", x, y);
        //sleep(1);
        get_mouse_coor(x, y, pars, env);
        usleep(200000);
        return (1); // replsace to 42
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
        while (i == 0)
        {
            render(env);
            i = kbhit();
            if (i != 0)
                read(1, pars.buf, 127);
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
            ft_putnbr(env->size / 2);
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