/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:23:13 by amaula            #+#    #+#             */
/*   Updated: 2024/08/26 13:24:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	max(int a, int b)
{
	if (a > b)
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
