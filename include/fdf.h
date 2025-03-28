/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:14:04 by alexanfe          #+#    #+#             */
/*   Updated: 2025/03/28 15:19:14 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <stdint.h>
# include <fcntl.h>

typedef struct s_map
{
	uint32_t	row_count;
	uint32_t	column_count;
	int			**matrix;
}	t_map;

uint32_t	get_rows(char *filename);
uint32_t	get_columns(char *filename);
t_map	*init_map(char *filename);
void	parse_map(char *filename, t_map *map);
void	print_map(t_map *map);
#endif
