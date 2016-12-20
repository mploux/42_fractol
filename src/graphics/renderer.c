/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 16:00:00 by mploux            #+#    #+#             */
/*   Updated: 2016/12/20 15:15:45 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphics.h"
#include "maths.h"

void	draw_text(t_data *data, t_vec2 pos, int color, char *string)
{
	mlx_string_put(data->mlx, data->win->ctx, pos.x + 1, pos.y + 2, 0, string);
	mlx_string_put(data->mlx, data->win->ctx, pos.x, pos.y, color, string);
}

void	draw_pix(t_data *data, double x, double y, int color)
{
	bitmap_draw_pix(data->framebuffer, (int)x, (int)y, color);
}

void	draw_line(t_data *data, t_vec2 a, t_vec2 b, t_vec2 colors)
{
	if (ABS(b.x - a.x) > ABS(b.y - a.y))
		draw_line_x(data, a, b, colors);
	else
		draw_line_y(data, a, b, colors);
}
