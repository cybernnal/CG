#ifndef CG_H
# define CG_H

#include "SDL.h"
#include "libft.h"

#define WIN_WIDTH   1200
#define WIN_HEIGHT  700
#define MAR         20

#define USAGE "Usage: |x;y;p| x: x position, y: y position, p: 1 = bot ; 2 = top ; 3 = left ; 4 = right || 'quit' for exit game"

#define UN_SET    0x00000000
#define NUL_SET   0x00000001
#define USE_SET   0x00000002
#define TOP       0x00000004
#define BOT       0x00000008
#define LEFT      0x00000010
#define RIGHT     0x00000020
#define P_ONE_SET 0x00000040
#define P_TWO_SET 0x00000080
#define P_SET(x)  (x & P_TWO_SET || x & P_ONE_SET) ? 1 : 0

#define WHITE   (Uint32) ((255 << 16) + (255 << 8) + 255)
#define RED     (Uint32) ((255 << 16) + (0 << 8) + 0)
#define GREEN   (Uint32) ((0 << 16) + (255 << 8) + 0)
#define BLEU    (Uint32) ((0 << 16) + (0 << 8) + 255)
#define PURPUL  (Uint32) ((108 << 16) + (2 << 8) + 119)
#define ORANGE  (Uint32) ((250 << 16) + (164 << 8) + 1)
#define P1COLOR PURPUL
#define P2COLOR ORANGE

typedef struct      s_trace
{
    int len;
    int x;
    int y;
    int x1;
    int y1;
    int marx;
    int mary;
    int p;
   }                   t_trace;

typedef struct      s_window
{ 
	SDL_Window      *window;
	SDL_Event       event;
	SDL_Renderer    *renderer;
	SDL_Texture     *image;
	Uint32          *img_ptr;
	int             is_init;
}                   t_window;

typedef struct      s_pars
{
    int             x;
    int             y;
    float           xm;
    float           ym;
    int             pos;
    char            buf[128];
}                   t_pars;

typedef struct      s_env
{
    int             ret;
    int             size;
    int             **map;
    int             p;
    int             p1;
    int             p2;
    int             ia;
}                   t_env;

typedef struct      s_ia
{
    unsigned int    p_3_1;
    unsigned int    p_3_2;
    unsigned int    p_3_3;
    unsigned int    p_3_4;
    unsigned int    last;
}                   t_ia;

void	render(t_env *env);
void	init_window(t_window *window);
int     creat_map(t_env *env);
void    ft_error(char *str);
void    set_point(t_env *env, int x, int y);
int    do_round(int x, int y, int p, t_env *env);
int     do_game(t_env * env);
void        print_map(int **map, int size);
void     put_masque(int x, int y, unsigned int pos, t_env *env);
int      ft_ia(t_env *env, t_pars *pars);

#endif
