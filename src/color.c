/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:20:57 by amaula            #+#    #+#             */
/*   Updated: 2024/09/04 12:04:21 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	hex_parser(char *hex)
{
	int			res;
	const char	*chars;

	chars = "0123456789ABCDEF";
	if (hex[0] != '0' || hex[1] != 'x')
		return (-1);
	hex += 2;
	res = 0;
	while (ft_strchr(chars, ft_toupper(*hex)))
	{
		res *= 16;
		res += ft_strchr(chars, ft_toupper(*hex)) - chars;
		hex++;
	}
	return (res);
}

void	set_colors(t_grid *grid)
{
	int		y;
	int		x;
	t_coord	*c;
	int		color;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			c = &grid->coords[y][x];
			if (c->z < 0 && grid->min_depth != 0)
				color = 255 - 255 * c->z / grid->min_depth;
			if (c->z >= 0 && grid->max_depth != 0)
				color = 255 - 255 * c->z / grid->max_depth;
			c->color = 255 << 16 | color << 8 | color;
			x++;
		}
		y++;
	}
}

static void	break_down(t_color *color, int code)
{
	color->r = (code >> 16) & 0xFF;
	color->g = (code >> 8) & 0xFF;
	color->b = code & 0xFF;
}

int	get_color(t_coord start, t_coord end, int len)
{
	double	t;
	t_color	start_color;
	t_color	end_color;
	t_color	pixel_color;

	if (len == 0)
		return (start.color);
	break_down(&start_color, start.color);
	break_down(&end_color, end.color);
	t = 1 - hypot(abs(start.x - end.x), abs(start.y - end.y)) / len;
	pixel_color.r = start_color.r + (end_color.r - start_color.r) * t;
	pixel_color.g = start_color.g + (end_color.g - start_color.g) * t;
	pixel_color.b = start_color.b + (end_color.b - start_color.b) * t;
	return (pixel_color.r << 16 | pixel_color.g << 8 | pixel_color.b);
}
