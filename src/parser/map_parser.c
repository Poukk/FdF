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

static void	parse_line(t_point *point, char *line)
{
	char	*color;
	char	saved;

	color = ft_strchr(line, ',');
	if (color)
	{
		saved = *color;
		*color = '\0';
		point->z = ft_atoi(line);
		*color = saved;
		point->color = convert_hex_color(color + 1);
	}
	else
	{
		point->z = ft_atoi(line);
		point->color = WHITE;
	}
}

/*
 * Returns the next token starting at `line`, updates `next` to the next cursor
 * position, and mutates the line in-place by replacing separators with '\0'.
 */
static char	*get_next_token(char *line, char **next)
{
	char	*start;

	if (!line)
		return (NULL);
	while (*line == ' ')
		line++;
	if (*line == '\0' || *line == '\n')
		return (NULL);
	start = line;
	while (*line && *line != ' ' && *line != '\n')
		line++;
	if (*line)
	{
		*line = '\0';
		line++;
	}
	*next = line;
	return (start);
}

void	parse_map(char *filename, t_map *map)
{
	uint32_t	i;
	uint32_t	j;
	char		*line;
	char		*token;
	char		*cursor;
	int			fd;

	fd = open(filename, O_RDONLY);
	i = 0;
	while (i < map->row_count)
	{
		line = get_next_line(fd);
		cursor = line;
		j = 0;
		while (j < map->column_count)
		{
			token = get_next_token(cursor, &cursor);
			if (!token)
			{
				free(line);
				clean_fd(fd);
				exit_error("Error: invalid map row\n");
			}
			parse_line(&map->points[i][j], token);
			map->points[i][j].x = j - (map->column_count / 2.0);
			map->points[i][j].y = i - (map->row_count / 2.0);
			j++;
		}
		free(line);
		i++;
	}
	clean_fd(fd);
}
