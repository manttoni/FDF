/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 14:21:35 by amaula            #+#    #+#             */
/*   Updated: 2024/07/29 13:55:01 by amaula           ###   ########.fr       */
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

typedef struct s_data
{
	void	*mlx;
	void	*win;
	int	height;
	int	width;
}	t_data;

typedef struct s_coord
{
	int	x;
	int y;
	int	z;
}	t_coord;

typedef struct s_grid
{
	t_coord	**coordinates;
	int		width;
	int		height;
	int		depth;
}	t_grid;

void test(t_data data);

int		max(int a, int b);
t_grid	*create_grid(char *file);
void	draw_grid(t_data data, t_grid *grid);
void	print_error(char *error_message);

#endif
