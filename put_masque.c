#include "cg.h"

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
void     put_masque(int x, int y, unsigned int pos, t_env *env)
{
    env->map[y][x] |= pos;
    env->map[y][x] |= USE_SET;
    if (pos == BOT)
        y++;
    else if (pos == TOP)
        y--;
    else if (pos == LEFT)
        x--;
    else if (pos == RIGHT)
        x++;
    else
        return ;
    pos = ret_not_pos(pos);
    if (x < 0 || x >= env->size || y < 0 || y >= env->size )
        return ;
        env->map[y][x] |= pos;
}
