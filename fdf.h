/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:21:35 by amaula            #+#    #+#             */
/*   Updated: 2024/08/27 13:45:38 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft/libft.h"
# include "get_next_line/get_next_line.h"
# include "mlx/mlx.h"
# include "ft_printf/ft_printf.h"
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

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}	t_coord;

typedef struct s_grid
{
	t_coord	**coords;
	int		width;
	int		height;
	int		depth;
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

int		is_visible(int size, t_coord c);
int		get_colour(t_grid *grid, t_coord current, t_coord end, int len);
int		init_data(t_data *data, int size);
void	free_data(t_data *data);
void	rotate(t_data *data, t_coord *coord);
int		max(int a, int b);
t_grid	*create_grid(char *file);
void	draw_grid(t_data *data);
void	print_error(char *error_message);

#endif
