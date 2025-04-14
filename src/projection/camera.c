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

static double	calculate_base_scale(t_map *map)
{
	double	scale_x;
	double	scale_y;
	double	base_scale;
	double	min_scale;
	double	padding_factor;

	padding_factor = 0.2;
	min_scale = 5.0;
	if (map->column_count <= 1 && map->row_count <= 1)
		return (20.0);
	else if (map->column_count <= 1)
		scale_x = WIDTH;
	else
		scale_x = (WIDTH * padding_factor) / map->column_count;
	if (map->row_count <= 1)
		scale_y = HEIGHT;
	else
		scale_y = (HEIGHT * padding_factor) / map->row_count;
	base_scale = fmin(scale_x, scale_y);
	return (fmax(base_scale, min_scale));
}

void	init_camera(t_fdf *fdf)
{
	fdf->camera = malloc(sizeof(t_camera));
	if (!fdf->camera)
		exit_error("Failed to allocate camera\n");
	fdf->camera->scale = calculate_base_scale(fdf->map);
	fdf->camera->x_angle = 0;
	fdf->camera->y_angle = 0;
	fdf->camera->z_angle = 0;
	fdf->camera->x_offset = WIDTH / 2;
	fdf->camera->y_offset = HEIGHT / 2;
}
