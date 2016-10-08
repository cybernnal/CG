#include <time.h>
#include <sys/time.h>
#include "cg.h"

static void key_handler(SDL_Event event)
{
	if (event.type == SDL_KEYDOWN)
	{
		if (event.key.keysym.sym == SDLK_ESCAPE)
			exit(EXIT_SUCCESS);
	}
}


static void draw_pixel(int x, int y, Uint32 color, t_window *w)
{
	w->img_ptr[WIN_WIDTH * y + x] = color;
}

static Uint32   get_rainbow_color( int i)
{ 
	int r, g, b;
	const float frequency = 0.01f;
	const int	n = WIN_HEIGHT / ( i + 0.0001f);

	r = ( int)( sinf( frequency * i + 0) * 127 + 128);
	g = ( int)( sinf( frequency * i + 2) * 127 + 128);
	b = ( int)( sinf( frequency * i + 4) * 127 + 128);
	return ( ( Uint32 )( ( r << 16) + ( g << 8) + b));
}

static Uint32 	get_top_color(t_env *env, int x, int y)
{
	printf("x: %d, y: %d\n", x, y);
	if (env->map[y][x] & UN_SET)
		return (WHITE);
	else if (env->map[y][x] & TOP || env->map[y][x] & BOT || env->map[y][x] & LEFT || env->map[y][x] & RIGHT)
		return (RED);
	else if (env->map[y][x] & P_ONE_SET)
		return (GREEN);
	else if (env->map[y][x] & P_TWO_SET)
		return (BLEU);
	else
		return (0);
}
/*

static Uint32 	get_bot_color(t_env *env, int x, int y)
{

}

static Uint32 	get_l_color(t_env *env, int x, int y)
{

}
*/

static Uint32 	get_r_color(t_env *env, int x, int y)
{

}

static void		draw_map(t_env *env, t_window *w)
{
	int x;
	int xmar;
	int y;
	int x1;
	int y1;
	int len;

	x1 = 0;
	y1 = 0;
	len = (WIN_HEIGHT - MAR * 2) / env->size;
	y = MAR;
	xmar = ((WIN_WIDTH - MAR * 2) % len);
	if (xmar < MAR)
		xmar += len;
	x = xmar;
	while (y <= WIN_HEIGHT - MAR)
	{
		while (x <= WIN_WIDTH - xmar)
		{
			if (x1 < env->size && y1 < env->size && ((y - MAR) % len == 0 || y == MAR || y == WIN_HEIGHT - MAR))
				draw_pixel(x, y, get_top_color(env, x1, y1), w);
			else if (x1 < env->size && y1 < env->size)
				draw_pixel(x, y, get_r_color(env, x1, y1), w);
			else
				draw_pixel(x, y, WHITE, w);
			if ((y - MAR) % len == 0 || y == MAR || y == WIN_HEIGHT - MAR)
				x++;
			else
			{
				x += len;
				x1++;
			}
		}
		//draw_pixel(WIN_WIDTH - xmar, y, WHITE, w);
		y++;
		if ((y - MAR) % len == 0 && y - MAR != 0)
			y1++;
		x = xmar;
		x1 = 0;
	}
}

void        render(t_env *env)
{
	static t_window w;

	if (!w.is_init)
	{
		init_window(&w);
		w.is_init = 1;
	}
	bzero(w.img_ptr, sizeof(Uint32) * WIN_HEIGHT * WIN_WIDTH);
	draw_map(env, &w);
	while (SDL_PollEvent(&w.event))
		key_handler(w.event);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
}
