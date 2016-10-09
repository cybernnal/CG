#include "cg.h"

void    set_point(t_env *env, int x, int y)
{
    env->ret = 1;
    if (env->p  == 1)
    {
        env->map[y][x] |= P_ONE_SET;
        env->p1++;
    }
    else
    {
        env->map[y][x] |= P_TWO_SET;
        env->p2++;
    }
}