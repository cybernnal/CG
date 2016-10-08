#include "cg.h"

void        print_map(int **map, int size)
{
    int x;
    int y;

    x = 0;
    y = 0;
    while (y < size) {
        while (x < size) {
            ft_putnbr(map[y][x]);
            x++;
        }
        x = 0;
        ft_putendl("");
        y++;
    }
}