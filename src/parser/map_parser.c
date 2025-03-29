/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 12:57:52 by alexanfe          #+#    #+#             */
/*   Updated: 2025/03/28 15:28:10 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"
#include <fcntl.h>

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
}

void	alloc_map(t_map *map, uint32_t rows, uint32_t columns)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < rows)
	{
		map->matrix[i] = (int *)malloc(columns * sizeof(int));
		if (!map->matrix[i])
		{
			j = 0;
			while (j < i)
			{
				free(map->matrix[j]);
				j++;
			}
			free(map->matrix);
			free(map);
		}
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
	columns = get_columns(filename);
	map->row_count = rows;
	map->column_count = columns;
	map->matrix = (int **)malloc(rows * sizeof(int *));
	if (!map->matrix)
	{
		free(map);
		return (NULL);
	}
	alloc_map(map, rows, columns);
	return (map);
}

void	parse_map(char *filename, t_map *map)
{
	uint32_t	i;
	uint32_t	j;
	char		*line;
	char		**splited_line;
	int			fd;

	i = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return ;
	while (i < map->row_count)
	{
		line = get_next_line(fd);
		splited_line = ft_split(line, ' ');
		j = 0;
		while (j < map->column_count)
		{
			map->matrix[i][j] = ft_atoi(splited_line[j]);
			j++;
		}
		free_split(splited_line);
		free(line);
		i++;
	}
	close(fd);
}

void	print_map(t_map *map)
{
	uint32_t	i;
	uint32_t	j;

	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < map->column_count)
		{
			ft_printf("%d ", map->matrix[i][j]);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}
