/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:58:04 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 13:45:06 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static double	get_height_range(t_map *map)
{
	double		min_z;
	double		max_z;
	uint32_t	i;
	uint32_t	j;

	min_z = map->points[0][0].z;
	max_z = map->points[0][0].z;
	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < map->column_count)
		{
			if (map->points[i][j].z < min_z)
				min_z = map->points[i][j].z;
			if (map->points[i][j].z > max_z)
				max_z = map->points[i][j].z;
			j++;
		}
		i++;
	}
	return (max_z - min_z);
}

static double	calculate_base_scale(t_map *map, double height_range)
{
	double	base_scale;
	double	height_factor;
	double	min_scale;

	base_scale = fmin(WIDTH / map->column_count / 2,
			HEIGHT / map->row_count / 2);
	if (height_range > 0)
	{
		height_factor = 4.0;
		if (map->column_count > 100 || map->row_count > 100)
			height_factor = 2.0;
		base_scale = fmin(base_scale, HEIGHT / (height_range * height_factor));
	}
	min_scale = 2.0;
	if (map->column_count > 100 || map->row_count > 100)
		min_scale = 3.0;
	return (fmax(base_scale, min_scale));
}

void	init_camera(t_fdf *fdf)
{
	double	height_range;

	fdf->camera = malloc(sizeof(t_camera));
	if (!fdf->camera)
		exit_error("Failed to allocate camera\n");
	height_range = get_height_range(fdf->map);
	fdf->camera->scale = calculate_base_scale(fdf->map, height_range);
	fdf->camera->x_angle = 0;
	fdf->camera->y_angle = 0;
	fdf->camera->z_angle = 0;
	fdf->camera->x_offset = WIDTH / 2;
	fdf->camera->y_offset = HEIGHT / 2;
}
