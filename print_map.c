#include "cg.h"

void        print_map(int **map, int size)
{
    int x;
    int y;
    int i;

    i = 0;
    x = 0;
    y = 0;
    ft_putstr("\\ ");
    while (i < size)
        ft_putnbr(i++);
    ft_putendl("");
    i = 0;
    ft_putstr("  ");
    while (i++ < size)
        ft_putchar('-');
    i = 0;
    ft_putendl("");
    while (y < size)
    {
        ft_putnbr(i);
        ft_putchar('|');
        i++;
        while (x < size)
        {
            if (map[y][x] & USE_SET)
                ft_putnbr(1);
            else
                ft_putnbr(0);
            //ft_putnbr(map[y][x]);
            x++;
        }
        x = 0;
        ft_putendl("");
        y++;
    }
}