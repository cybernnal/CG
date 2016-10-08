#include "cg.h"


int	main(int argc, char **argv)
{
	t_env env;

    if (argc == 1)
        ft_error("not enough argument, map size needed");
	ft_bzero(&env, sizeof(t_env));
    env.size = ft_atoi(argv[1]);
	creat_map(&env);
    do_game(&env);
    print_map(env.map, env.size);
    if (env.p1 > env.p2)
        ft_putendl("GG p1 you win");
    else if (env.p1 < env.p2)
        ft_putendl("GG p2 you win");
    else
        ft_putendl("no winner");
    //while (1)
	//	render(3);
//	trace_map(3);
	return (1);
}
