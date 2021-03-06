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
  //  SDL_UpdateTexture(w->image, NULL, w->img_ptr, WIN_WIDTH * sizeof(Uint32));
    //SDL_RenderCopy(w->renderer, w->image, NULL, NULL);
    //SDL_RenderPresent(w->renderer);

}

static void     init_var(t_trace *var, t_env *env)
{
    if (!var->len)
    {
        var->len = ((WIN_HEIGHT - MAR * 2)) / env->size;
        var->marx = (WIN_WIDTH - (var->len * env->size)) / 2;
        var->mary = (WIN_HEIGHT - (var->len * env->size)) / 2;
    }
    var->p = env->p;
    var->x = var->marx;
    var->y = var->mary;
    var->x1 = 0;
    var->y1 = 0;
}

static int   get_p1set_color(t_env *env, t_trace *var, unsigned int pos)
{
    if (pos & TOP)
        if (var->y1 > 0 && env->map[var->y1 - 1][var->x1] & P_ONE_SET)
           return (1);
    if (pos & BOT)
        if (var->y1 < env->size - 1 && env->map[var->y1 + 1][var->x1] & P_ONE_SET)
            return (1);
    if (pos & LEFT)
        if (var->x1 > 0 && env->map[var->y1][var->x1 - 1] & P_ONE_SET)
            return (1);
    if (pos & RIGHT)
        if (var->x1 < env->size - 1 && env->map[var->y1][var->x1 + 1] & P_ONE_SET)
            return (1);
    return (0);

}

static int   get_p2set_color(t_env *env, t_trace *var, unsigned int pos)
{
    if (pos & TOP)
        if (var->y1 > 0 && env->map[var->y1 - 1][var->x1] & P_TWO_SET)
            return (1);
    if (pos & BOT)
        if (var->y1 < env->size - 1 && env->map[var->y1 + 1][var->x1] & P_TWO_SET)
            return (1);
    if (pos & LEFT)
        if (var->x1 > 0 && env->map[var->y1][var->x1 - 1] & P_TWO_SET)
            return (1);
    if (pos & RIGHT)
        if (var->x1 < env->size - 1 && env->map[var->y1][var->x1 + 1] & P_TWO_SET)
            return (1);
    return (0);

}


static Uint32   get_gen_color(t_env *env, t_trace *var, unsigned int pos)
{
    if (env->map[var->y1][var->x1] & P_ONE_SET || get_p1set_color(env, var, pos)) //(var->y1 > 0 && env->map[var->y1 - 1][var->x1] & P_ONE_SET))
        return (P1COLOR);
    else if (env->map[var->y1][var->x1] & P_TWO_SET || get_p2set_color(env, var, pos))// || (var->y1 > 0 && env->map[var->y1 - 1][var->x1] & P_TWO_SET))
        return (P2COLOR);
    else if (env->map[var->y1][var->x1] & pos)
        return (RED);
    else
        return (WHITE);
}

static void     draw_squar(t_window *w, t_trace *var, int pos)
{
    Uint32  color;

    if (pos & P_TWO_SET)
        color = P2COLOR;
    else
        color = P1COLOR;
    while ((var->y + 1 - var->mary) % var->len != 0)
    {
        while ((var->x + 1 - var->marx) % var->len != 0)
        {
            draw_pixel(var->x, var->y, color, w);
            var->x++;
        }
        draw_pixel(var->x, var->y, color, w);
        var->x = var->marx + var->x1 * var->len;
        var->y++;
    }
    while ((var->x + 1 - var->marx) % var->len != 0)
    {
        draw_pixel(var->x, var->y, color, w);
        var->x++;
    }
    draw_pixel(var->x, var->y, color, w);
    var->x = var->marx + var->x1 * var->len;
    var->y = var->mary + var->y1 * var->len;
}

static void     draw_map(t_env *env, t_window *w)
{
    static t_trace      var;

     init_var(&var, env);
    while (var.y1 < env->size)
    {
        while (var.x1 < env->size)
        {
            if (P_SET(env->map[var.y1][var.x1]))
                draw_squar(w, &var, env->map[var.y1][var.x1]);
            else
            {
                while ((var.x + 1 - var.marx) % var.len != 0)
                {
                    if (var.y1 == env->size - 1)
                        draw_pixel(var.x, var.y + var.len, get_gen_color(env, &var, BOT), w);
                    draw_pixel(var.x, var.y, get_gen_color(env, &var,TOP), w);
                    var.x++;
                }
                draw_pixel(var.x, var.y, get_gen_color(env, &var, TOP), w);
                var.x = var.marx + var.x1 * var.len;
                while ((var.y + 1 - var.mary) % var.len != 0)
                {
                    if (var.x1 == env->size - 1)
                        draw_pixel(var.x + var.len, var.y, get_gen_color(env, &var,RIGHT), w);

                    draw_pixel(var.x, var.y, get_gen_color(env, &var, LEFT), w);
                    var.y++;
                }
                draw_pixel(var.x, var.y, get_gen_color(env, &var, LEFT), w);
            }
            var.x1++;
            var.x = var.marx + var.x1 * var.len;
            var.y = var.mary + var.y1 * var.len;
        }
        var.x1 = 0;
        var.y1++;
        var.x = var.marx;
        var.y = var.mary + var.y1 * var.len;
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
