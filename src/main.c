/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mploux <mploux@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 14:07:59 by mploux            #+#    #+#             */
/*   Updated: 2016/12/20 14:42:56 by mploux           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "graphics.h"
#include <stdlib.h>
#include <fcntl.h>

int		main(int ac, char **av)
{
	t_data	*data;

	(void) av;
	if (ac != 2)
		error("usage: fractol fractal_name");
	if (ft_strcmp(av[1], "mandelbrot") != 0 &&
		ft_strcmp(av[1], "julia") &&
		ft_strcmp(av[1], "koch"))
		error("fractals:\n\tmandelbrot\n\tjulia\n\tkoch");
	if (!(data = (t_data *)ft_memalloc(sizeof(t_data))))
		error("malloc error !");
	if (ft_strcmp(av[1], "mandelbrot") == 0)
		data->fractal = 0;
	if (ft_strcmp(av[1], "julia") == 0)
		data->fractal = 1;
	if (ft_strcmp(av[1], "koch") == 0)
		data->fractal = 2;
	create_fractol(data, "Fractol !", 720, 720);
	loop_fractol(data);
	return (0);
}
