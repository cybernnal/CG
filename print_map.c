#include "cg.h"

void        print_map(int **map, int size)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < size)
    {
        while (x < size)
        {
            if (map[y][x] & P_TWO_SET || map[y][x] & P_ONE_SET)
                ft_putnbr(2);
            else if (map[y][x] & USE_SET)
                ft_putnbr(1);
            else
                ft_putnbr(0);
            x++;
        }
        x = 0;
        ft_putendl("");
        y++;
    }
}