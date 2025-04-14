/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 17:30:07 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 17:31:22 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include "ft_printf.h"
#include "libft.h"

void	exit_error(char	*message)
{
	ft_printf(message);
	exit(EXIT_FAILURE);
}

void	*map_error(t_map *map, void *message)
{
	free(map);
	ft_printf("Error: %s\n", (char *)message);
	return (NULL);
}

void	*fd_error(int fd)
{
	close(fd);
	return (NULL);
}

void	validate_filename(char *filename)
{
	size_t	len;

	if (access(filename, R_OK) == -1)
		exit_error("Error: File does not exist or cannot be read.\n");
	len = ft_strlen(filename);
	if (len < 5 || ft_strncmp(filename + len - 4, ".fdf", 4) != 0)
		exit_error("Error: Filename must end with '.fdf'.\n");
}
