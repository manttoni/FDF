/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:23:13 by amaula            #+#    #+#             */
/*   Updated: 2024/08/27 12:46:39 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	convert_rad(double angle)
{
	return (angle * (M_PI / 180));
}

void	rotate(t_data *data, t_coord *coord)
{
	double	angle;
	double	len;
	t_coord	origo;

	origo.x = data->size / 2;
	origo.y = data->size / 2;
	angle = atan2(0, 1) - atan2(coord->y - origo.y, coord->x - origo.x);
	angle += convert_rad(data->perspective);
	angle = -angle;
	len = hypot(coord->x - origo.x, coord->y - origo.y);
	coord->x = (int)(len * cos(angle)) + origo.x;
	coord->y = (int)(len * sin(angle)) + origo.y;
}

int	get_colour(t_grid *grid, t_coord current, t_coord end, int len)
{
	int	drawn;
	int start_colour;
	int	end_colour;
	int	pixel_colour;

	if (len == 0)
		return (0);
	start_colour = 255 - 255 * current.z / grid->depth;
	end_colour = 255 - 255 * end.z / grid->depth;
	drawn = len - hypot(abs(current.x - end.x), abs(current.y - end.y));
	pixel_colour = 255 - start_colour - (drawn * (end_colour - start_colour) / len); 
	return (255 << 16 | pixel_colour << 8 | pixel_colour);
}
