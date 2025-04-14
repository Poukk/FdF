/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:44:03 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 17:31:42 by alexanfe         ###   ########.fr       */
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
# define COLUNMN_ERROR "could not parse columns"
# define ROW_ERROR "could not parse rows"
# define POINTS_ERROR "could not parse maps to points"

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

typedef struct s_camera
{
	double	scale;
	double	x_angle;
	double	y_angle;
	double	z_angle;
	int		x_offset;
	int		y_offset;
}	t_camera;

typedef struct s_fdf
{
	mlx_t		*mlx;
	mlx_image_t	*img;
	t_map		*map;
	t_camera	*camera;
}	t_fdf;

/* Map parsing*/
t_map		*init_map(char *filename);
void		parse_map(char *filename, t_map *map);
uint32_t	get_rows(char *filename);
uint32_t	get_columns(char *filename);

/* Color parsing */
uint32_t	interpolate_color(t_point start, t_point end, double percentage);
uint32_t	convert_hex_color(char *hex_str);

/* Drawing */
void		init_image(t_fdf *fdf);
void		draw_line(mlx_image_t *img, t_point start, t_point end);
void		draw_map(t_fdf *fdf);
void		put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);

/* Projection */
t_point		project_point(t_point point, t_camera *camera);
void		init_camera(t_fdf *fdf);

/* Drawing helpers */
double		get_percentage(double current, double start, double delta);
void		update_bresenham_low(t_line *line);
void		update_bresenham_high(t_line *line);
int			is_point_in_screen(int x, int y);

/* Clenup handling */
void		free_map(t_map *map);
void		clean_fd(int fd);
void		free_split(char **splited);

/* Error handling */
void		exit_error(char *message);
void		*map_error(t_map *map, void *message);
void		*fd_error(int fd);
#endif
