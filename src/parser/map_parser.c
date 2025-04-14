/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:57:52 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 12:56:31 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "libft.h"
#include "fdf.h"

void	alloc_map(t_map *map, uint32_t rows, uint32_t columns)
{
	uint32_t	i;

	i = 0;
	while (i < rows)
	{
		map->points[i] = (t_point *)malloc(columns * sizeof(t_point));
		if (!map->points[i])
			free_map(map);
		i++;
	}
}

t_map	*init_map(char *filename)
{
	uint32_t	rows;
	uint32_t	columns;
	t_map		*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (NULL);
	rows = get_rows(filename);
	if (!rows)
		return (map_error(map, ROW_ERROR));
	columns = get_columns(filename);
	if (!columns)
		return (map_error(map, COLUNMN_ERROR));
	map->row_count = rows;
	map->column_count = columns;
	map->points = (t_point **)malloc(rows * sizeof(t_point *));
	if (!map->points)
		return (map_error(map, POINTS_ERROR));
	alloc_map(map, rows, columns);
	return (map);
}

void	parse_line(t_point *point, char *line)
{
	char	**splited;

	if (ft_strchr(line, ','))
	{
		splited = ft_split(line, ',');
		point->z = ft_atoi(splited[0]);
		point->color = convert_hex_color(splited[1]);
		free_split(splited);
	}
	else
	{
		point->z = ft_atoi(line);
		point->color = WHITE;
	}
}

void	parse_map(char *filename, t_map *map)
{
	uint32_t	i;
	uint32_t	j;
	char		*line;
	char		**splited_line;
	int			fd;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < map->row_count)
	{
		line = get_next_line(fd);
		splited_line = ft_split(line, ' ');
		j = 0;
		while (j < map->column_count)
		{
			parse_line(&map->points[i][j], splited_line[j]);
			map->points[i][j].x = j - (map->column_count / 2.0);
			map->points[i][j].y = i - (map->row_count / 2.0);
			j++;
		}
		free_split(splited_line);
		free(line);
		i++;
	}
	clean_fd(fd);
}
