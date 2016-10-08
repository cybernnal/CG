#include "cg.h"

static Uint32   get_rainbow_color(int i)
{
    int r, g, b;
    const float frequency = 0.01f;
    const int	n = WIN_HEIGHT / (i + 0.0001f);

    r = (int)(sinf(frequency * i + 0) * 127 + 128);
    g = (int)(sinf(frequency * i + 2) * 127 + 128);
    b = (int)(sinf(frequency * i + 4) * 127 + 128);
    return ((Uint32 )((r << 16) + (g << 8) + b));
}


static void init_texture_renderer(t_window *win, int w, int h)
{
	if (!(win->img_ptr = (Uint32 *)ft_memalloc(sizeof(Uint32) * w * h)))
		exit(EXIT_FAILURE);
	win->image = SDL_CreateTexture(win->renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);
}

void        init_window(t_window *window)
{
	SDL_Init(SDL_INIT_VIDEO);
	if (!(window->window = SDL_CreateWindow("push_swap", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
					WIN_WIDTH, WIN_HEIGHT, SDL_WINDOW_SHOWN)))
		exit(EXIT_FAILURE);
	if (!(window->renderer = SDL_CreateRenderer(window->window, -1, SDL_RENDERER_ACCELERATED)))
		exit(EXIT_FAILURE);
	init_texture_renderer(window, WIN_WIDTH, WIN_HEIGHT);
//	window->step_x = WIN_WIDTH / get_env()->total_size;
//	window->step_y = WIN_HEIGHT / 4;
}
