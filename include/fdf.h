/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 15:14:04 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/11 13:34:23 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include <stdint.h>
# include <fcntl.h>

# define WIDTH 1920
# define HEIGHT 1080
# define WHITE 0xFFFFFFFF
# define RED 0xFF0000FF
# define GREEN 0x00FF00FF
# define BLUE 0x0000FFFF

typedef struct s_point
{
	double		x;
	double		y;
	int32_t		z;
	uint32_t	color;
}	t_point;

typedef struct s_line
{
	int	dx;
	int	dy;
	int	xi;
	int	yi;
	int	d;
	int	x;
	int	y;
}	t_line;

typedef struct s_map
{
	t_point		**points;
	uint32_t	row_count;
	uint32_t	column_count;
}	t_map;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
}	t_fdf;

// Map functions
t_map		*init_map(char *filename);
void		parse_map(char *filename, t_map *map);
uint32_t	get_rows(char *filename);
uint32_t	get_columns(char *filename);

// Drawing functions
void		init_image(t_fdf *fdf);
void		put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
void		draw_line(mlx_image_t *img, t_point start, t_point end);
void		init_image(t_fdf *fdf);
void		put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
uint32_t	interpolate_color(t_point start, t_point end, double percentage);

// Error handling and cleanup
void		exit_error(char *message);
void		free_map(t_map *map);
void		clean_fd(int fd);
void		free_split(char **splited);
void		*map_error(t_map *map);

// Debug functions
void		print_map(t_map *map);
void		draw_test_lines(t_fdf *fdf);

#endif
