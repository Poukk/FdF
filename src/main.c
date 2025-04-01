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

#include "fdf.h"
#include "ft_printf.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void	free_map(t_map *map)
{
	uint32_t	i;

	i = 0;
	while (i < map->row_count)
	{
		free(map->matrix[i]);
		i++;
	}
	free(map->matrix);
	free(map);
}

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
			ft_printf("%d ", map->matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2)
	{
		ft_printf("Usage: ./fdf <map_file>\n");
		return (EXIT_FAILURE);
	}
	map = init_map(argv[1]);
	if (!map)
	{
		ft_printf("Error initializing map");
		return (EXIT_FAILURE);
	}
	parse_map(argv[1], map);
	print_map(map);
	free_map(map);
	return (EXIT_SUCCESS);
}
