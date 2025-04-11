/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 17:49:25 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/11 13:26:43 by alexanfe         ###   ########.fr       */
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

void	draw_test_lines(t_fdf *fdf)
{
	t_point	p1;
	t_point	p2;

	p1 = (t_point){.x = 100, .y = 100, .z = 0, .color = 0xFFFFFFFF};
	p2 = (t_point){.x = 300, .y = 100, .z = 0, .color = 0xFF0000FF};
	draw_line(fdf->img, p1, p2);
	p1 = (t_point){.x = 200, .y = 50, .z = 0, .color = 0x0000FFFF};
	p2 = (t_point){.x = 200, .y = 250, .z = 0, .color = 0x00FF00FF};
	draw_line(fdf->img, p1, p2);
	p1 = (t_point){.x = 100, .y = 100, .z = 0, .color = 0xFFFF00FF};
	p2 = (t_point){.x = 300, .y = 300, .z = 0, .color = 0xFF00FFFF};
	draw_line(fdf->img, p1, p2);
}
