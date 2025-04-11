/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:20:11 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/11 13:34:10 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void	setup_line_low(t_line *line, t_point start, t_point end)
{
	line->dx = end.x - start.x;
	line->dy = end.y - start.y;
	line->yi = 1;
	if (line->dy < 0)
	{
		line->yi = -1;
		line->dy = -line->dy;
	}
	line->d = (2 * line->dy) - line->dx;
	line->y = start.y;
	line->x = start.x;
}

static void	draw_line_low(mlx_image_t *img, t_point start, t_point end)
{
	t_line	line;
	double	percentage;

	setup_line_low(&line, start, end);
	while (line.x <= end.x)
	{
		percentage = (double)(line.x - start.x) / (end.x - start.x);
		put_pixel(img, line.x, line.y,
			interpolate_color(start, end, percentage));
		if (line.d > 0)
		{
			line.y = line.y + line.yi;
			line.d = line.d + (2 * (line.dy - line.dx));
		}
		else
			line.d = line.d + 2 * line.dy;
		line.x++;
	}
}

static void	setup_line_high(t_line *line, t_point start, t_point end)
{
	line->dx = end.x - start.x;
	line->dy = end.y - start.y;
	line->xi = 1;
	if (line->dx < 0)
	{
		line->xi = -1;
		line->dx = -line->dx;
	}
	line->d = (2 * line->dx) - line->dy;
	line->x = start.x;
	line->y = start.y;
}

static void	draw_line_high(mlx_image_t *img, t_point start, t_point end)
{
	t_line	line;
	double	percentage;

	setup_line_high(&line, start, end);
	while (line.y <= end.y)
	{
		percentage = (double)(line.y - start.y) / (end.y - start.y);
		put_pixel(img, line.x, line.y,
			interpolate_color(start, end, percentage));
		if (line.d > 0)
		{
			line.x = line.x + line.xi;
			line.d = line.d + (2 * (line.dx - line.dy));
		}
		else
			line.d = line.d + 2 * line.dx;
		line.y++;
	}
}

void	draw_line(mlx_image_t *img, t_point start, t_point end)
{
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
	{
		if (start.x > end.x)
			draw_line_low(img, end, start);
		else
			draw_line_low(img, start, end);
	}
	else
	{
		if (start.y > end.y)
			draw_line_high(img, end, start);
		else
			draw_line_high(img, start, end);
	}
}
