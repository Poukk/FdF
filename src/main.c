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

int	main(int argc, char *argv[])
{
	t_map	*map;

	if (argc != 2)
	{
		write(2, "Usage: ./fdf <map_file>\n", 24);
		return (EXIT_FAILURE);
	}
	map = init_map(argv[1]);
	if (!map)
	{
		perror("Error initializing map");
		return (EXIT_FAILURE);
	}
	parse_map(argv[1], map);
	print_map(map);
	free_map(map);
	return (EXIT_SUCCESS);
}
