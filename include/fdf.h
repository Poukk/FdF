/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:14:04 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/01 08:50:27 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# define WIDTH 1920
# define HEIGHT 1080
# include <stdint.h>
# include <fcntl.h>

typedef struct s_point
{
	uint32_t	z;
	uint32_t	color;
}	t_point;

typedef struct s_map
{
	uint32_t	row_count;
	uint32_t	column_count;
	t_point		**points;
}	t_map;

uint32_t	get_rows(char *filename);
uint32_t	get_columns(char *filename);
t_map	*init_map(char *filename);
void	parse_map(char *filename, t_map *map);
void	print_map(t_map *map);
void	clean_fd(int fd);
void	*map_error(t_map *map);
void	free_split(char **splited);
void	clean_fd(int fd);
void	exit_error(char	*message);
void	free_map(t_map *map);
#endif
