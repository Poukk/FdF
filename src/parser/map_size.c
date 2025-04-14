/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:17:35 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 17:32:59 by alexanfe         ###   ########.fr       */
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

static void	trim_trailing_whitespace(char *line)
{
	int	len;

	if (!line)
		return ;
	len = ft_strlen(line);
	while (len > 0 && (line[len - 1] == ' ' || line[len - 1] == '\t'
			|| line[len - 1] == '\n'))
	{
		line[len - 1] = '\0';
		len--;
	}
}

static int	is_line_column_valid(char *line, uint32_t expected_columns)
{
	uint32_t	current_columns;

	if (!line)
		return (0);
	trim_trailing_whitespace(line);
	current_columns = count_words(line, ' ');
	if (*line == '\0')
	{
		return (current_columns == expected_columns);
	}
	return (current_columns == expected_columns);
}

static uint32_t	get_initial_columns(int fd, char **first_line_ptr)
{
	char		*line;
	uint32_t	columns;

	line = get_next_line(fd);
	if (!line)
		return (0);
	trim_trailing_whitespace(line);
	columns = count_words(line, ' ');
	*first_line_ptr = line;
	return (columns);
}

uint32_t	get_columns(char *filename)
{
	uint32_t	columns;
	char		*line;
	int			fd;
	int			is_valid;

	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (0);
	line = NULL;
	columns = get_initial_columns(fd, &line);
	if (!line)
		fd_error(fd);
	while (line)
	{
		is_valid = is_line_column_valid(line, columns);
		free(line);
		if (!is_valid)
		{
			clean_fd(fd);
			return (0);
		}
		line = get_next_line(fd);
	}
	close(fd);
	return (columns);
}
