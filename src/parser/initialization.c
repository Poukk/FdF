/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialization.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:51:18 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 17:51:24 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_image(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		exit_error("Error creating image\n");
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
	{
		mlx_terminate(fdf->mlx);
		exit_error("Error putting image to window\n");
	}
}

void	init_fdf(t_fdf *fdf, char *filename)
{
	fdf->map = init_map(filename);
	if (!fdf->map)
		exit_error("Error initializing map\n");
	parse_map(filename, fdf->map);
	mlx_set_setting(MLX_FULLSCREEN, true);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
	{
		free_map(fdf->map);
		exit_error("Error initializing MLX\n");
	}
	init_image(fdf);
	init_camera(fdf);
}
