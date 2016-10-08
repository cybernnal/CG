#ifndef CG_H
# define CG_H

//#include <sdl2.h>
//#include "SDL2/SDL.h"
#include "libft.h"

#define WIN_WIDTH   1000
#define WIN_HEIGHT  500

#define USAGE "Usage: |x;y;p| x: x position, y: y position, p: 1 = bot ; 2 = top ; 3 = left ; 4 = right"

#define UN_SET    0x00000000
#define NUL_SET   0x00000001
#define USE_SET   0x00000002
#define TOP       0x00000004
#define BOT       0x00000008
#define LEFT      0x00000010
#define RIGHT     0x00000020
#define P_ONE_SET 0x00000040
#define P_TWO_SET 0x00000080
#define SET       TOP & BOT & LEFT & RIGHT


/*

typedef struct      s_window
{ 
	SDL_Window      *window;
	SDL_Event       event;
	SDL_Renderer    *renderer;
	SDL_Texture     *image;
	Uint32          *img_ptr;
	int             is_init;
	int             step_x;
	int             step_y;
}                   t_window;
*/

typedef struct      s_pars
{
    int             x;
    int             y;
    int             pos;
}                   t_pars;

typedef struct      s_env
{
    int             size;
    int             **map;
    int             p;
    int             p1;
    int             p2;
}                   t_env;

//void	render(int size);
//void	init_window(t_window *window);
//void	build_map(int size);
int     creat_map(t_env *env);
void    ft_error(char *str);
void    set_point(t_env *env, int x, int y);
int    do_round(int x, int y, int p, t_env *env);
int     do_game(t_env * env);
void        print_map(int **map, int size);

#endif
