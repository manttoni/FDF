/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:21:35 by amaula            #+#    #+#             */
/*   Updated: 2024/08/26 13:18:58 by amaula           ###   ########.fr       */
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
	t_grid	*grid;
	t_image	*image;
}	t_data;

int		init_data(t_data *data, int size);
void	free_data(t_data *data);
void	rotate(t_data *data, t_coord *coord);
int		max(int a, int b);
t_grid	*create_grid(char *file);
void	draw_grid(t_data *data);
void	print_error(char *error_message);

#endif
