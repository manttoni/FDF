/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 11:42:38 by amaula            #+#    #+#             */
/*   Updated: 2024/09/04 11:51:28 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	change_perspective(t_data *data, int key)
{
	if (key == LEFT_ARROW)
		data->perspective += 10;
	else
		data->perspective --;
}

void	change_zoom(t_data *data, int key)
{
	if (key == UP_ARROW)
		data->zoom++;
	else
		data->zoom--;
}

void	move_camera(t_data *data, int key)
{
	if (key == W)
		data->camera.y++;
	if (key == A)
		data->camera.x++;
	if (key == S)
		data->camera.y--;
	if (key == D)
		data->camera.x--;
}

void	reset_all(t_data *data)
{
	data->zoom = 0;
	data->perspective = 0;
	data->camera.x = 0;
	data->camera.y = 0;
}
