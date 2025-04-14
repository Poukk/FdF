/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:20:20 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:28:55 by alexanfe         ###   ########.fr       */
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

static void	draw_line_low(mlx_image_t *img, t_point start, t_point end)
{
	t_line	line;
	double	percentage;
	double	delta_x;

	setup_line_low(&line, start, end);
	delta_x = end.x - start.x;
	while (line.x <= end.x)
	{
		if (is_point_in_screen(line.x, line.y))
		{
			percentage = get_percentage(line.x, start.x, delta_x);
			put_pixel(img, line.x, line.y,
				interpolate_color(start, end, percentage));
		}
		update_bresenham_low(&line);
	}
}

static void	draw_line_high(mlx_image_t *img, t_point start, t_point end)
{
	t_line	line;
	double	percentage;
	double	delta_y;

	setup_line_high(&line, start, end);
	delta_y = end.y - start.y;
	while (line.y <= end.y)
	{
		if (is_point_in_screen(line.x, line.y))
		{
			percentage = get_percentage(line.y, start.y, delta_y);
			put_pixel(img, line.x, line.y,
				interpolate_color(start, end, percentage));
		}
		update_bresenham_high(&line);
	}
}

void	draw_line(mlx_image_t *img, t_point start, t_point end)
{
	if (start.x == end.x && start.y == end.y)
	{
		if (is_point_in_screen(start.x, start.y))
			put_pixel(img, start.x, start.y, start.color);
		return ;
	}
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
