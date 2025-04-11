/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:49:25 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/09 17:49:57 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"

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
			ft_printf("[%i][%i]: %d", i, j, map->points[i][j].z);
			if (map->points[i][j].color)
				ft_printf(", %x | ", map->points[i][j].color);
			else
				ft_printf(", %d | ", 0);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
