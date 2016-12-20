/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/15 20:18:06 by mploux            #+#    #+#             */
/*   Updated: 2016/12/20 17:35:05 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "graphics.h"

static int	interpolate_color(t_data *data, t_vec2 z, int i)
{
	double	n;
	int		a;
	int		b;
	double	h;

	h = data->height;
	if (data->smooth_shading)
	{
		n = log((log(z.x * z.x + z.y * z.y) / 2.0) / log(2)) / log(2);
		a = color_angle((int)(floor(i + 1 - n) * h + data->color), 0);
		b = color_angle((int)((floor(i + 1 - n) + 1) * h + data->color), 0);
		return (col_lerp(b, a, fmod(n, 1.0)));
	}
	return (color_angle(i * h + data->color, 0));
}

static void	draw_pixel(t_data *data, t_vec2 c, t_vec2 pix, int iteration)
{
	double	i;
	double	old_zx;
	t_vec2	z;
	int		color;

	i = 0;
	z = vec2(0, 0);
	while (z.x * z.x + z.y * z.y < 16 && i < iteration)
	{
		old_zx = z.x;
		z.x = z.x * z.x - z.y * z.y + c.x;
		z.y = 2 * old_zx * z.y + c.y;
		i++;
	}
	if (i < iteration)
	{
		color = interpolate_color(data, z, i);
		draw_pix(data, (int)pix.x, (int)pix.y, color);
	}
}

static void	manage_keys(t_data *data)
{
	double mx;
	double my;

	mx = (double)data->input->x;
	my = (double)data->input->y;
	if (data->input->key[KEY_C])
		data->color += 6;
	if (data->input->key[KEY_V])
		data->color -= 6;
	if (data->input->button == 4 || data->input->key[KEY_UP])
	{
		data->mouse.x += (mx / data->win->w - 0.5) * data->zoom / 10;
		data->mouse.y += (my / data->win->h - 0.5) * data->zoom / 10;
		data->zoom /= 1.1;
	}
	if (data->input->button == 5 || data->input->key[KEY_DOWN])
	{
		data->mouse.x += (mx / data->win->w - 0.5) * data->zoom / 10;
		data->mouse.y += (my / data->win->h - 0.5) * data->zoom / 10;
		data->zoom /= 0.9;
	}
}

void		draw_mandelbrot(t_data *data)
{
	t_vec2	c;
	t_vec2	n;
	int		max_i;

	manage_keys(data);
	c.y = -1;
	while (++c.y < data->win->h)
	{
		c.x = -1;
		while (++c.x < data->win->w)
		{
			n.x = ((c.x / data->win->w - 0.5) * data->zoom) + data->mouse.x;
			n.y = ((c.y / data->win->h - 0.5) * data->zoom) + data->mouse.y;
			max_i = 50 - log(data->zoom);
			draw_pixel(data, vec2(n.x, n.y), vec2(c.x, c.y), max_i);
		}
	}
}
