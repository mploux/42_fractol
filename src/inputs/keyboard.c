/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/16 01:21:39 by mploux            #+#    #+#             */
/*   Updated: 2016/12/20 12:59:30 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"

int			key_hook(int key, t_data *data)
{
	if (key == KEY_ESCAPE)
		exit_fractol(data);
	if (key == KEY_1)
		data->smooth_shading = 1 - data->smooth_shading;
	data->input->key[key] = 1;
	return (1);
}

int			key_up_hook(int key, t_data *data)
{
	data->input->key[key] = 0;
	return (1);
}
