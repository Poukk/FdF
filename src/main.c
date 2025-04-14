/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:31 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 17:51:28 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "fdf.h"

void	escape_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf;

	fdf = (t_fdf *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
	{
		free_map(fdf->map);
		free(fdf->camera);
		mlx_terminate(fdf->mlx);
		exit(EXIT_SUCCESS);
	}
}

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
		exit_error("Usage: ./fdf <map_file>\n");
	validate_filename(argv[1]);
	init_fdf(&fdf, argv[1]);
	mlx_key_hook(fdf.mlx, &escape_hook, &fdf);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	return (EXIT_SUCCESS);
}
