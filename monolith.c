// === HEADERS ===
/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   fdf.h											  :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: alexanfe <alexanfe@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2025/03/28 15:14:04 by alexanfe		  #+#	#+#			 */
/*   Updated: 2025/04/11 13:34:23 by alexanfe		 ###   ########.fr	   */
/*																			*/
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

// Map functions
t_map		*init_map(char *filename);
void		parse_map(char *filename, t_map *map);
uint32_t	get_rows(char *filename);
uint32_t	get_columns(char *filename);

// Drawing functions
void		init_image(t_fdf *fdf);
void		draw_line(mlx_image_t *img, t_point start, t_point end);
uint32_t	interpolate_color(t_point start, t_point end, double percentage);
void		init_camera(t_fdf *fdf);
t_point		project_point(t_point point, t_camera *camera);
void		draw_map(t_fdf *fdf);
uint32_t	convert_hex_color(char *hex_str);
void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color);
int	is_point_in_screen(int x, int y);
double	get_percentage(double current, double start, double delta);
void	update_bresenham_low(t_line *line);
void	update_bresenham_high(t_line *line);

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
// === SOURCES ===
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:09:31 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:28:50 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "MLX42/MLX42.h"
#include "fdf.h"

void	init_image(t_fdf *fdf)
{
	fdf->img = mlx_new_image(fdf->mlx, WIDTH, HEIGHT);
	if (!fdf->img)
		exit_error("Error creating image\n");
	if (mlx_image_to_window(fdf->mlx, fdf->img, 0, 0) == -1)
	{
		mlx_terminate(fdf->mlx);
		exit_error("Error putting image to window\n");
	}
}

void	init_fdf(t_fdf *fdf, char *filename)
{
	fdf->map = init_map(filename);
	if (!fdf->map)
		exit_error("Error initializing map\n");
	parse_map(filename, fdf->map);
	mlx_set_setting(MLX_FULLSCREEN, true);
	fdf->mlx = mlx_init(WIDTH, HEIGHT, "FdF", true);
	if (!fdf->mlx)
	{
		free_map(fdf->map);
		exit_error("Error initializing MLX\n");
	}
	init_image(fdf);
	init_camera(fdf);
}

int	main(int argc, char *argv[])
{
	t_fdf	fdf;

	if (argc != 2)
		exit_error("Usage: ./fdf <map_file>\n");
	init_fdf(&fdf, argv[1]);
	draw_map(&fdf);
	mlx_loop(fdf.mlx);
	mlx_terminate(fdf.mlx);
	free_map(fdf.map);
	free(fdf.camera);
	return (EXIT_SUCCESS);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isometric.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:44:32 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 13:45:01 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

static void	rotate_x(double *y, double *z, double angle)
{
	double	prev_y;

	prev_y = *y;
	*y = prev_y * cos(angle) + *z * sin(angle);
	*z = -prev_y * sin(angle) + *z * cos(angle);
}

static void	rotate_y(double *x, double *z, double angle)
{
	double	prev_x;

	prev_x = *x;
	*x = prev_x * cos(angle) + *z * sin(angle);
	*z = -prev_x * sin(angle) + *z * cos(angle);
}

static void	rotate_z(double *x, double *y, double angle)
{
	double	prev_x;

	prev_x = *x;
	*x = prev_x * cos(angle) - *y * sin(angle);
	*y = prev_x * sin(angle) + *y * cos(angle);
}

t_point	project_point(t_point point, t_camera *camera)
{
	t_point	projected;
	double	x;
	double	y;
	double	z;

	x = point.x * camera->scale;
	y = point.y * camera->scale;
	z = point.z * (camera->scale * 0.5);
	rotate_x(&y, &z, camera->x_angle);
	rotate_y(&x, &z, camera->y_angle);
	rotate_z(&x, &y, camera->z_angle);
	projected.x = (x - y) * cos(0.523599) + camera->x_offset;
	projected.y = -z + (x + y) * sin(0.523599) + camera->y_offset;
	projected.z = point.z;
	projected.color = point.color;
	return (projected);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 11:58:04 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 13:45:06 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include <stdlib.h>

static double	get_height_range(t_map *map)
{
	double		min_z;
	double		max_z;
	uint32_t	i;
	uint32_t	j;

	min_z = map->points[0][0].z;
	max_z = map->points[0][0].z;
	i = 0;
	while (i < map->row_count)
	{
		j = 0;
		while (j < map->column_count)
		{
			if (map->points[i][j].z < min_z)
				min_z = map->points[i][j].z;
			if (map->points[i][j].z > max_z)
				max_z = map->points[i][j].z;
			j++;
		}
		i++;
	}
	return (max_z - min_z);
}

static double	calculate_base_scale(t_map *map, double height_range)
{
	double	base_scale;
	double	height_factor;
	double	min_scale;

	base_scale = fmin(WIDTH / map->column_count / 2,
			HEIGHT / map->row_count / 2);
	if (height_range > 0)
	{
		height_factor = 4.0;
		if (map->column_count > 100 || map->row_count > 100)
			height_factor = 2.0;
		base_scale = fmin(base_scale, HEIGHT / (height_range * height_factor));
	}
	min_scale = 2.0;
	if (map->column_count > 100 || map->row_count > 100)
		min_scale = 3.0;
	return (fmax(base_scale, min_scale));
}

void	init_camera(t_fdf *fdf)
{
	double	height_range;

	fdf->camera = malloc(sizeof(t_camera));
	if (!fdf->camera)
		exit_error("Failed to allocate camera\n");
	height_range = get_height_range(fdf->map);
	fdf->camera->scale = calculate_base_scale(fdf->map, height_range);
	fdf->camera->x_angle = 0;
	fdf->camera->y_angle = 0;
	fdf->camera->z_angle = 0;
	fdf->camera->x_offset = WIDTH / 2;
	fdf->camera->y_offset = HEIGHT / 2;
}
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
		return (map_error(map));
	columns = get_columns(filename);
	if (!columns)
		return (map_error(map));
	map->row_count = rows;
	map->column_count = columns;
	map->points = (t_point **)malloc(rows * sizeof(t_point *));
	if (!map->points)
		return (map_error(map));
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
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:19:03 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:30:00 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

uint32_t	interpolate_color(t_point start, t_point end, double percentage)
{
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (percentage < 0.0)
		percentage = 0.0;
	if (percentage > 1.0)
		percentage = 1.0;
	r = ((start.color >> 24) & 0xFF) * (1 - percentage)
		+ ((end.color >> 24) & 0xFF) * percentage;
	g = ((start.color >> 16) & 0xFF) * (1 - percentage)
		+ ((end.color >> 16) & 0xFF) * percentage;
	b = ((start.color >> 8) & 0xFF) * (1 - percentage)
		+ ((end.color >> 8) & 0xFF) * percentage;
	a = (start.color & 0xFF) * (1 - percentage)
		+ (end.color & 0xFF) * percentage;
	return (r << 24 | g << 16 | b << 8 | a);
}

uint32_t	convert_hex_color(char *hex_str)
{
	uint32_t	hex_value;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (hex_str[0] == '0' && (hex_str[1] == 'x' || hex_str[1] == 'X'))
		hex_str += 2;
	hex_value = ft_strtol(hex_str, NULL, 16);
	r = (hex_value >> 16) & 0xFF;
	g = (hex_value >> 8) & 0xFF;
	b = hex_value & 0xFF;
	a = 0xFF;
	return ((r << 24) | (g << 16) | (b << 8) | a);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 12:06:51 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 12:08:07 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "fdf.h"

void	draw_connections(t_fdf *fdf, t_point current, uint32_t x, uint32_t y)
{
	t_point	right;
	t_point	down;

	if (x < fdf->map->column_count - 1)
	{
		right = project_point(fdf->map->points[y][x + 1], fdf->camera);
		draw_line(fdf->img, current, right);
	}
	if (y < fdf->map->row_count - 1)
	{
		down = project_point(fdf->map->points[y + 1][x], fdf->camera);
		draw_line(fdf->img, current, down);
	}
}

void	draw_map(t_fdf *fdf)
{
	uint32_t	x;
	uint32_t	y;
	t_point		current_projected;

	ft_memset(fdf->img->pixels, 0, fdf->img->width
		* fdf->img->height * sizeof(int));
	y = 0;
	while (y < fdf->map->row_count)
	{
		x = 0;
		while (x < fdf->map->column_count)
		{
			current_projected = project_point(fdf->map->points[y][x],
					fdf->camera);
			draw_connections(fdf, current_projected, x, y);
			x++;
		}
		y++;
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:20:20 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:28:55 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "fdf.h"

static void	setup_line_low(t_line *line, t_point start, t_point end)
{
	line->dx = end.x - start.x;
	line->dy = end.y - start.y;
	line->yi = 1;
	if (line->dy < 0)
	{
		line->yi = -1;
		line->dy = -line->dy;
	}
	line->d = (2 * line->dy) - line->dx;
	line->y = start.y;
	line->x = start.x;
}

static void	setup_line_high(t_line *line, t_point start, t_point end)
{
	line->dx = end.x - start.x;
	line->dy = end.y - start.y;
	line->xi = 1;
	if (line->dx < 0)
	{
		line->xi = -1;
		line->dx = -line->dx;
	}
	line->d = (2 * line->dx) - line->dy;
	line->x = start.x;
	line->y = start.y;
}

static void	draw_line_low(mlx_image_t *img, t_point start, t_point end)
{
	t_line	line;
	double	percentage;
	double	delta_x;

	setup_line_low(&line, start, end);
	delta_x = end.x - start.x;
	while (line.x <= end.x)
	{
		if (is_point_in_screen(line.x, line.y))
		{
			percentage = get_percentage(line.x, start.x, delta_x);
			put_pixel(img, line.x, line.y,
				interpolate_color(start, end, percentage));
		}
		update_bresenham_low(&line);
	}
}

static void	draw_line_high(mlx_image_t *img, t_point start, t_point end)
{
	t_line	line;
	double	percentage;
	double	delta_y;

	setup_line_high(&line, start, end);
	delta_y = end.y - start.y;
	while (line.y <= end.y)
	{
		if (is_point_in_screen(line.x, line.y))
		{
			percentage = get_percentage(line.y, start.y, delta_y);
			put_pixel(img, line.x, line.y,
				interpolate_color(start, end, percentage));
		}
		update_bresenham_high(&line);
	}
}

void	draw_line(mlx_image_t *img, t_point start, t_point end)
{
	if (start.x == end.x && start.y == end.y)
	{
		if (is_point_in_screen(start.x, start.y))
			put_pixel(img, start.x, start.y, start.color);
		return ;
	}
	if (fabs(end.y - start.y) < fabs(end.x - start.x))
	{
		if (start.x > end.x)
			draw_line_low(img, end, start);
		else
			draw_line_low(img, start, end);
	}
	else
	{
		if (start.y > end.y)
			draw_line_high(img, end, start);
		else
			draw_line_high(img, start, end);
	}
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 16:01:01 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/14 16:29:13 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	is_point_in_screen(int x, int y)
{
	return (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT);
}

double	get_percentage(double current, double start, double delta)
{
	if (delta == 0)
		return (0.0);
	else
		return ((current - start) / delta);
}

void	update_bresenham_low(t_line *line)
{
	if (line->d > 0)
	{
		line->y += line->yi;
		line->d += (2 * (line->dy - line->dx));
	}
	else
		line->d += 2 * line->dy;
	line->x++;
}

void	update_bresenham_high(t_line *line)
{
	if (line->d > 0)
	{
		line->x += line->xi;
		line->d += (2 * (line->dx - line->dy));
	}
	else
		line->d += 2 * line->dx;
	line->y++;
}

void	put_pixel(mlx_image_t *img, uint32_t x, uint32_t y, uint32_t color)
{
	uint8_t		*pixel_ptr;
	uint32_t	r;
	uint32_t	g;
	uint32_t	b;
	uint32_t	a;

	if (x >= img->width || y >= img->height)
		return ;
	pixel_ptr = img->pixels + (y * img->width + x) * 4;
	r = (color >> 24) & 0xFF;
	g = (color >> 16) & 0xFF;
	b = (color >> 8) & 0xFF;
	a = color & 0xFF;
	pixel_ptr[0] = r;
	pixel_ptr[1] = g;
	pixel_ptr[2] = b;
	pixel_ptr[3] = a;
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexanfe <alexanfe@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 08:45:23 by alexanfe          #+#    #+#             */
/*   Updated: 2025/04/01 08:50:31 by alexanfe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "fdf.h"
#include "ft_printf.h"
#include "get_next_line.h"

void	free_split(char **splited)
{
	int	i;

	i = 0;
	while (splited[i] != NULL)
		free(splited[i++]);
	free(splited);
}

void	free_map(t_map *map)
{
	uint32_t	i;

	i = 0;
	while (i < map->row_count)
	{
		free(map->points[i]);
		i++;
	}
	free(map->points);
	free(map);
}

void	clean_fd(int fd)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	exit_error(char	*message)
{
	ft_printf(message);
	exit(EXIT_FAILURE);
}

void	*map_error(t_map *map)
{
	free(map);
	return (NULL);
}
