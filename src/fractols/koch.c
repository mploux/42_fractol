/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   koch.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/20 14:40:36 by mploux            #+#    #+#             */
/*   Updated: 2016/12/20 17:14:35 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "graphics.h"

static int	is_in_view(t_data *data, t_vec2 a, t_vec2 b)
{
	if ((a.x < 0 && b.x < 0) || (a.y < 0 && b.y < 0))
		return (0);
	if ((a.x >= data->win->w && b.x >= data->win->w) ||
		(a.y >= data->win->h && b.y >= data->win->h))
		return (0);
	return (1);
}

static void	draw_elem(t_data *data, t_vec2 a, t_vec2 b, int i)
{
	t_vec2	a_mid;
	t_vec2	b_mid;
	t_vec2	mid;
	t_vec2	mid_step;

	a_mid = vec2(LERP(a.x, b.x, 1.0 / 3.0), LERP(a.y, b.y, 1.0 / 3.0));
	b_mid = vec2(LERP(a.x, b.x, 2.0 / 3.0), LERP(a.y, b.y, 2.0 / 3.0));
	mid_step.x = (b_mid.y - a_mid.y) * sin(DTR(60));
	mid_step.y = -(b_mid.x - a_mid.x) * sin(DTR(60));
	mid.x = LERP(a.x, b.x, 1.0 / 2.0) + mid_step.x;
	mid.y = LERP(a.y, b.y, 1.0 / 2.0) + mid_step.y;
	if (i++ > data->max_i - 1)
	{
		if (!is_in_view(data, a, b))
			return;
		draw_line(data, a, a_mid, vec2(0xffffff, 0xffffff));
		draw_line(data, a_mid, mid, vec2(0xffffff, 0xffffff));
		draw_line(data, mid, b_mid, vec2(0xffffff, 0xffffff));
		draw_line(data, b_mid, b, vec2(0xffffff, 0xffffff));
		return;
	}
	draw_elem(data, a, a_mid, i);
	draw_elem(data, a_mid, mid, i);
	draw_elem(data, mid, b_mid, i);
	draw_elem(data, b_mid, b, i);
}

void		draw_koch(t_data *data)
{
	static double i = 120;
	static double scale = 100;
	static double speed = 1;

	if (data->input->key[KEY_LEFT])
		i -= 0.01;
	if (data->input->key[KEY_RIGHT])
		i += 0.01;
	if (data->input->button == 4 || data->input->key[KEY_UP])
	{
		data->mouse.x += (data->input->x - data->win->w / 2) * 0.01 / speed;
		data->mouse.y += (data->input->y - data->win->h / 2) * 0.01 / speed;
		scale *= 1.01;
		speed *= 1.01;
		data->max_i += 0.007;
	}
	if (data->input->button == 5 || data->input->key[KEY_DOWN])
	{
		data->mouse.x += (data->input->x - data->win->w / 2) * 0.01 / speed;
		data->mouse.y += (data->input->y - data->win->h / 2) * 0.01 / speed;
		scale *= 0.99;
		speed *= 0.99;
		data->max_i -= 0.007;
	}
	t_vec2 a;
	t_vec2 b;
	t_vec2 c;

	a.x = cos(DTR(i - 59)) * scale + data->win->w / 2 - data->mouse.x * speed;
	a.y = sin(DTR(i - 59)) * scale + data->win->h / 2 - data->mouse.y * speed;
	b.x = cos(DTR(i + 60)) * scale + data->win->w / 2 - data->mouse.x * speed;
	b.y = sin(DTR(i + 60)) * scale + data->win->h / 2 - data->mouse.y * speed;
	c.x = cos(DTR(i + 180)) * scale + data->win->w / 2 - data->mouse.x * speed;
	c.y = sin(DTR(i + 180)) * scale + data->win->h / 2 - data->mouse.y * speed;
	draw_elem(data, a, b, 0);
	draw_elem(data, c, a, 0);
	draw_elem(data, b, c, 0);
}
