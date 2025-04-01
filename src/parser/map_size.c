/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:17:35 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/01 08:46:39 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

uint32_t	get_rows(char *filename)
{
	uint32_t	rows;
	char		*line;
	int			fd;

	rows = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	while (line)
	{
		rows++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (rows);
}

uint32_t	get_columns(char *filename)
{
	uint32_t	columns;
	uint32_t	temp;
	char		*line;
	int			fd;

	columns = 0;
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = get_next_line(fd);
	columns = count_words(line, ' ');
	while (line)
	{
		temp = count_words(line, ' ');
		if (temp != columns)
		{
			free(line);
			clean_fd(fd);
			return (0);
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (columns);
}
