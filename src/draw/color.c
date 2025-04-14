/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 16:02:30 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/12 16:02:31 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	interpolate_color(t_point start, t_point end, double percentage)
{
	uint8_t	r;
	uint8_t	g;
	uint8_t	b;
	uint8_t	a;

	r = ((end.color >> 24) & 0xFF) * percentage + ((start.color >> 24) & 0xFF)
		* (1 - percentage);
	g = ((end.color >> 16) & 0xFF) * percentage + ((start.color >> 16) & 0xFF)
		* (1 - percentage);
	b = ((end.color >> 8) & 0xFF) * percentage + ((start.color >> 8) & 0xFF)
		* (1 - percentage);
	a = (end.color & 0xFF) * percentage + (start.color & 0xFF)
		* (1 - percentage);
	return (r << 24 | g << 16 | b << 8 | a);
}
