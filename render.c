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


static void		draw_map(t_env *env, t_window *w)
{
	int x;
	int xmar;
	int y;
	int len;

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
			draw_pixel(x, y, BLEU, w);
			if ((y - MAR) % len == 0 || y == MAR || y == WIN_HEIGHT - MAR)
				x++;
			else
				x += len;
		}
		draw_pixel(WIN_WIDTH - xmar, y, BLEU, w);
		y++;
		x = xmar;
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
