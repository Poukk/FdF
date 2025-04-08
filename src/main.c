/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:37:20 by alexanfe          #+#    #+#             */
/*   Updated: 2025/03/28 15:39:50 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include "ft_printf.h"
#include <stdlib.h>
#include <unistd.h>

void	print_map(t_map *map)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < map->column_count)
		{
			ft_printf("%d ", map->points[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

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
	mlx_loop(mlx);
	mlx_terminate(mlx);

	free_map(map);
	return (EXIT_SUCCESS);
}
