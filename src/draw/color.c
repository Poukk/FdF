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
#include "libft.h"

uint32_t	interpolate_color(t_point start, t_point end, double percentage)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (percentage < 0.0)
		percentage = 0.0;
	if (percentage > 1.0)
		percentage = 1.0;
	r = ((start.color >> 24) & 0xFF) * (1 - percentage)
		+ ((end.color >> 24) & 0xFF) * percentage;
	g = ((start.color >> 16) & 0xFF) * (1 - percentage)
		+ ((end.color >> 16) & 0xFF) * percentage;
	b = ((start.color >> 8) & 0xFF) * (1 - percentage)
		+ ((end.color >> 8) & 0xFF) * percentage;
	a = (start.color & 0xFF) * (1 - percentage)
		+ (end.color & 0xFF) * percentage;
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	convert_hex_color(char *hex_str)
{
	uint32_t	hex_color;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	hex_color = ft_strtol(hex_str, (char **) NULL, 16);
	if (hex_color <= 0xFF)
	{
		r = hex_color;
		g = hex_color;
		b = hex_color;
		a = 0xFF;
	}
	else
	{
		r = (hex_color >> 16) & 0xFF;
		g = (hex_color >> 8) & 0xFF;
		b = hex_color & 0xFF;
		a = 0xFF;
	}
	return (r << 24 | g << 16 | b << 8 | a);
}
