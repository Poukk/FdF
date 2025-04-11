/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:37:20 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/09 17:51:59 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "fdf.h"

int	main(int argc, char *argv[])
{
	t_map	*map;
	mlx_t	*mlx;

	if (argc != 2)
		exit_error("Usage: ./fdf <map_file>\n");
	map = init_map(argv[1]);
	if (!map)
		exit_error("Error initializing map\n");
	parse_map(argv[1], map);
	print_map(map);
	mlx_set_setting(MLX_FULLSCREEN, true);
	mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!mlx)
		exit_error("Error initializing map\n");
	mlx_terminate(mlx);
	free_map(map);
	return (EXIT_SUCCESS);
}
