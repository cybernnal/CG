#include "cg.h"

static t_env        *sig(t_env *env, int i)
{
    static t_env *save;

    if (i == 1)
        save = env;
    return (save);
}

static void                at_exit(void)
{
    t_env   *env;
    int     i;
    char    buf[2];

    ft_bzero(buf, 2);
    env = sig(NULL, 0);
    i = 0;
    render(env);
    while (i < env->size)
    {
        ft_memdel((void**)&env->map[i]);
        i++;
    }
    ft_memdel((void**)&env->map);
    printf("\nGame process terminated, score: Player 1: %d, Player 2: %d\n GG Player %d you win", env->p1, env->p2, env->p1 > env->p2 ? 1 : 2);
    if (env->p1 + env->p2 >= ((env->size + 1) * (env->size / 2) + 1))
        while (env->size)
            render(env);
}

int	main(int argc, char **argv)
{
	t_env env;

    if (argc == 1)
        ft_error("not enough or too many argument, map size needed");
    atexit(at_exit);
	ft_bzero(&env, sizeof(t_env));
    sig(&env, 1);
    env.size = ft_atoi(argv[1]);
	creat_map(&env);
    if (argv[2])
    {
        if (!ft_strcmp(argv[2], "1"))
            env.ia = 1;
        else if (!ft_strcmp(argv[2], "2"))
            env.ia = 2;
    }
    do_game(&env);
    print_map(env.map, env.size);
    render(&env);
    if (env.p1 > env.p2)
        ft_putendl("GG p1 you win");
    else if (env.p1 < env.p2)
        ft_putendl("GG p2 you win");
    else
        ft_putendl("no winner");
	return (1);
}
