/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:19:03 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:30:00 by alexanfe         ###   ########.fr       */
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
	uint32_t	hex_value;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	hex_value = ft_strtol(hex_str, NULL, 16);
	r = (hex_value >> 16) & 0xFF;
	g = (hex_value >> 8) & 0xFF;
	b = hex_value & 0xFF;
	a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
