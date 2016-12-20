/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:12:44 by mploux            #+#    #+#             */
/*   Updated: 2016/12/20 16:55:53 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "maths.h"
#include "graphics.h"
#include <stdlib.h>

int		create_fractol(t_data *data, const char *name, int width, int height)
{
	t_win		*win;

	if (!(win = (t_win *)ft_memalloc(sizeof(t_win))))
		error("malloc error !");
	if (!(data->mlx = mlx_init()))
		error("mlx error: mlx failed to load !");
	win->w = width;
	win->h = height;
	win->name = (char *)name;
	if (!(win->ctx = mlx_new_window(data->mlx, win->w, win->h, win->name)))
		error("mlx error: win failed to load !");
	data->win = win;
	data->input = new_input();
	data->framebuffer = new_bitmap(data, width, height);
	data->color = 0;
	data->zoom = 4;
	data->mouse = vec2(0, 0);
	data->smooth_shading = 0;
	data->height = 5;
	data->max_i = 4;
	data->draw_fractal[0] = &draw_mandelbrot;
	data->draw_fractal[1] = &draw_julia;
	data->draw_fractal[2] = &draw_koch;
	return (1);
}

void	draw_debug(t_data *data)
{
	int y;

	y = data->win->h;
	draw_text(data, vec2(5, y - 25), 0xffffff, "Ecole 42 - Fractol - mploux");
}

int		loop(t_data *data)
{
	if (data->input->key[KEY_Z])
		data->height += 1;
	if (data->input->key[KEY_X])
		data->height -= 1;
	data->draw_fractal[data->fractal](data);
	mlx_put_image_to_window(data->mlx, data->win->ctx, data->framebuffer->ctx,
																		0, 0);
	draw_debug(data);
	clear_bitmap(data->framebuffer);
	data->input->button = 0;
	return (1);
}

void	loop_fractol(t_data *data)
{
	mlx_hook(data->win->ctx, 2, (1L << 0), &key_hook, data);
	mlx_hook(data->win->ctx, 3, (1L << 1), &key_up_hook, data);
	mlx_hook(data->win->ctx, 6, (1L << 6), &mouse_pos_hook, data);
	mlx_mouse_hook(data->win->ctx, &mouse_hook, data);
	mlx_loop_hook(data->mlx, &loop, data);
	mlx_loop(data->mlx);
}

void	exit_fractol(t_data *data)
{
	mlx_destroy_window(data->mlx, data->win->ctx);
	mlx_destroy_image(data->mlx, data->framebuffer->ctx);
	free(data->input);
	free(data);
	exit(0);
}
