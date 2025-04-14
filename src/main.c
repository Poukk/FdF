/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:31 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 12:10:44 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "fdf.h"

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

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
		exit_error("Usage: ./fdf <map_file>\n");
	init_fdf(&fdf, argv[1]);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(fdf.map);
	free(fdf.camera);
	return (EXIT_SUCCESS);
}
