/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 13:21:09 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/11 13:21:11 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_image(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		exit_error("Error creating image\n");
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
	{
		mlx_terminate(fdf->mlx);
		exit_error("Error putting image to window\n");
	}
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint32_t	*pixel;

	if (x >= WIDTH || y >= HEIGHT)
		return ;
	pixel = (uint32_t *)(img->pixels + (y * img->width + x) * sizeof(uint32_t));
	*pixel = color;
}
