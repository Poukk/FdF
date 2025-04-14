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
