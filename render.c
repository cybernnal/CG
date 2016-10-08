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

static void		draw_map(int size, t_window *w)
{
	int x;
	int y;
	int len;

	len = (WIN_HEIGHT - 40) / size;
	x = (WIN_WIDTH / 2) - len / 2;
	y = (WIN_HEIGHT / 2) - ((size / 2) * len);
	//ft_putnbr(y);
	while (len--)
	{
		draw_pixel(x, y, (Uint32) ((255 << 16) + (0 << 8) + 0), w);
		x++;
	}
}

void        render(int size)
{
	static t_window w;

	if (!w.is_init)
	{
		init_window(&w);
		w.is_init = 1;
	}
	bzero(w.img_ptr, sizeof(Uint32) * WIN_HEIGHT * WIN_WIDTH);
	draw_map(size, &w);
	while (SDL_PollEvent(&w.event))
		key_handler(w.event);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
}
