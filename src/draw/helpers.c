/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:01:01 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:29:13 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_point_in_screen(int x, int y)
{
	return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

double	get_percentage(double current, double start, double delta)
{
	if (delta == 0)
		return (0.0);
	else
		return ((current - start) / delta);
}

void	update_bresenham_low(t_line *line)
{
	if (line->d > 0)
	{
		line->y += line->yi;
		line->d += (2 * (line->dy - line->dx));
	}
	else
		line->d += 2 * line->dy;
	line->x++;
}

void	update_bresenham_high(t_line *line)
{
	if (line->d > 0)
	{
		line->x += line->xi;
		line->d += (2 * (line->dx - line->dy));
	}
	else
		line->d += 2 * line->dx;
	line->y++;
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t		*pixel_ptr;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (x >= img->width || y >= img->height)
		return ;
	pixel_ptr = img->pixels + (y * img->width + x) * 4;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	pixel_ptr[0] = r;
	pixel_ptr[1] = g;
	pixel_ptr[2] = b;
	pixel_ptr[3] = a;
}
