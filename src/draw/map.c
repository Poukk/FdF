/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:06:51 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 12:08:07 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	draw_connections(t_fdf *fdf, t_point current, uint32_t x, uint32_t y)
{
	t_point	right;
	t_point	down;

	if (x < fdf->map->column_count - 1)
	{
		right = project_point(fdf->map->points[y][x + 1], fdf->camera);
		draw_line(fdf->img, current, right);
	}
	if (y < fdf->map->row_count - 1)
	{
		down = project_point(fdf->map->points[y + 1][x], fdf->camera);
		draw_line(fdf->img, current, down);
	}
}

void	draw_map(t_fdf *fdf)
{
	uint32_t	x;
	uint32_t	y;
	t_point		current_projected;

	ft_memset(fdf->img->pixels, 0, fdf->img->width
		* fdf->img->height * sizeof(int));
	y = 0;
	while (y < fdf->map->row_count)
	{
		x = 0;
		while (x < fdf->map->column_count)
		{
			current_projected = project_point(fdf->map->points[y][x],
					fdf->camera);
			draw_connections(fdf, current_projected, x, y);
			x++;
		}
		y++;
	}
}
