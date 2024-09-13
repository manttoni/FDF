/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:06:07 by amaula            #+#    #+#             */
/*   Updated: 2024/09/04 12:29:06 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_data(t_data *data, int size)
{
	t_image	*i;
	char	*top;

	top = "ARROWS=zoom/rotate, WASD=move, DELETE=reset";
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, size, size, top);
	if (data->win == NULL)
		return (1);
	data->image = malloc(sizeof(t_image));
	if (data->image == NULL)
		return (1);
	i = data->image;
	i->img = mlx_new_image(data->mlx, size, size);
	if (i->img == NULL)
		return (1);
	i->img_data = mlx_get_data_addr(i->img, &(i->bpp), &(i->sl), &(i->endian));
	if (i->img_data == NULL)
		return (1);
	data->size = size;
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->grid->height)
	{
		free(data->grid->coords[i]);
		i++;
	}
	free(data->grid->coords);
	free(data->grid);
	mlx_destroy_image(data->mlx, data->image->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->image);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}
