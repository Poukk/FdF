/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:44:32 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 13:45:01 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	rotate_x(double *y, double *z, double angle)
{
	double	prev_y;

	prev_y = *y;
	*y = prev_y * cos(angle) + *z * sin(angle);
	*z = -prev_y * sin(angle) + *z * cos(angle);
}

static void	rotate_y(double *x, double *z, double angle)
{
	double	prev_x;

	prev_x = *x;
	*x = prev_x * cos(angle) + *z * sin(angle);
	*z = -prev_x * sin(angle) + *z * cos(angle);
}

static void	rotate_z(double *x, double *y, double angle)
{
	double	prev_x;

	prev_x = *x;
	*x = prev_x * cos(angle) - *y * sin(angle);
	*y = prev_x * sin(angle) + *y * cos(angle);
}

t_point	project_point(t_point point, t_camera *camera)
{
	t_point	projected;
	double	x;
	double	y;
	double	z;

	x = point.x * camera->scale;
	y = point.y * camera->scale;
	z = point.z * (camera->scale * 0.5);
	rotate_x(&y, &z, camera->x_angle);
	rotate_y(&x, &z, camera->y_angle);
	rotate_z(&x, &y, camera->z_angle);
	projected.x = (x - y) * cos(0.523599) + camera->x_offset;
	projected.y = -z + (x + y) * sin(0.523599) + camera->y_offset;
	projected.z = point.z;
	projected.color = point.color;
	return (projected);
}
