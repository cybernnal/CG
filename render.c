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

static void     init_var(t_trace *var, t_env *env)
{
    if (!var->len)
    {
        var->len = (WIN_HEIGHT - MAR * 2) / env->size;
        var->marx = (WIN_WIDTH - (var->len * env->size)) / 2;
        var->mary = (WIN_HEIGHT - (var->len * env->size)) / 2;
    }
    var->x = var->marx;
    var->y = var->mary;
    var->x1 = 0;
    var->y1 = 0;
    var->ll = 0;
}

static Uint32   get_color(t_env *env, t_trace *var)
{
    if (var->y1 >= env->size || var->x1 >= env->size)
        return (WHITE);
    if (env->map[var->y1][var->x1] & P_ONE_SET)
        return (GREEN);
    else if (env->map[var->y1][var->x1] & P_TWO_SET)
        return (BLEU);
    else if (var->y == WIN_HEIGHT - var->mary || var->ll == 1)
        return (WHITE);
    else if ((var->y - var->mary) % var->len == 0 || var->y == var->mary || var->y == WIN_HEIGHT - var->mary)
    {
        if (env->map[var->y1][var->x1] & TOP)
            return (RED);
        else
            return (WHITE);
    }
    else
    {
        if (env->map[var->y1][var->x1] & LEFT)
            return (RED);
        else
            return (WHITE);
    }

}

static void     draw_it(t_env *env, t_window *w)
{
    static t_trace     var;

    init_var(&var, env);
    while (var.y <= WIN_HEIGHT - var.mary)
    {
        while (var.x <= WIN_WIDTH - var.marx)
        {
            draw_pixel(var.x, var.y, get_color(env, &var), w);
            if ((var.y - var.mary) % var.len == 0 || var.y == var.mary || var.y == WIN_HEIGHT - var.mary || P_SET(env->map[var.y1][var.x1]))
            {
                var.x++;
                if ((var.x - var.marx) % var.len == 0 && var.x1 < 8)
                    var.x1++;
            }
            else
            {
                var.x += var.len;
                if (var.x1 < 8)
                    var.x1++;
            }
        }
        var.x1 = 0;
        var.y++;
        if ((var.y - var.mary) % var.len == 0)
        {
            if (var.y1 != 8)
                var.y1++;
 //           else if (var.ll == 1)
   //             return;
            else
                var.ll = 1;
        }
        var.x = var.marx;
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
	draw_it(env, &w);
	while (SDL_PollEvent(&w.event))
		key_handler(w.event);
	SDL_UpdateTexture(w.image, NULL, w.img_ptr, WIN_WIDTH * sizeof(Uint32));
	SDL_RenderCopy(w.renderer, w.image, NULL, NULL);
	SDL_RenderPresent(w.renderer);
}
