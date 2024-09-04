/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:21:35 by amaula            #+#    #+#             */
/*   Updated: 2024/09/04 12:25:33 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "../lib/libft/libft.h"
# include "../lib/get_next_line/get_next_line.h"
# include "../lib/mlx/mlx.h"
# include "../lib/ft_printf/ft_printf.h"
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <unistd.h>
# include <fcntl.h>

# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define ESCAPE_KEY 65307
# define W 119
# define A 97
# define S 115
# define D 100
# define DELETE 65535

typedef struct s_file_reader
{
	char	*file;
	char	*ptr;
	char	*line;
	int		x;
	int		fd;
}	t_file_reader;

typedef struct s_color
{
	int	r;
	int	g;
	int	b;
}	t_color;

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bresenham;

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
	int	color;
}	t_coord;

typedef struct s_grid
{
	t_coord	**coords;
	int		width;
	int		height;
	int		max_depth;
	int		min_depth;
	int		default_colors;
}	t_grid;

typedef struct s_image
{
	void	*img;
	char	*img_data;
	int		bpp;
	int		sl;
	int		endian;
}	t_image;

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int		size;
	int		perspective;
	int		zoom;
	t_coord	camera;
	t_grid	*grid;
	t_image	*image;
}	t_data;

void	swap(t_coord *a, t_coord *b);
void	change_perspective(t_data *data, int key);
void	change_zoom(t_data *data, int key);
void	move_camera(t_data *data, int key);
void	reset_all(t_data *data);
int		hex_parser(char *hex);
int		is_visible(int size, t_coord start, t_coord end);
void	set_colors(t_grid *grid);
int		get_color(t_coord current, t_coord end, int len);
int		init_data(t_data *data, int size);
void	free_data(t_data *data);
void	rotate(t_data *data, t_coord *coord);
int		max(int a, int b);
int		min(int a, int b);
t_grid	*create_grid(char *file);
void	draw_grid(t_data *data);

#endif
