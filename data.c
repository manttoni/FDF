/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:06:07 by amaula            #+#    #+#             */
/*   Updated: 2024/08/26 12:16:26 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	init_data(t_data *data, int size)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
		return (1);
	data->win = mlx_new_window(data->mlx, size, size, "FDF");
	if (data->win == NULL)
		return (1);
	data->image = malloc(sizeof(t_image));
	if (data->image == NULL)
		return (1);
	data->image->img = mlx_new_image(data->mlx, size, size);
	data->image->img_data = mlx_get_data_addr(data->image->img, &(data->image->bits_per_pixel), &(data->image->size_line), &(data->image->endian));
	data->size = size;
	data->perspective = 0;
	return (0);
}

void	free_data(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->grid->height)
	{
		free(data->grid->coordinates[i]);
		i++;
	}
	free(data->grid->coordinates);
	free(data->grid);
	mlx_destroy_image(data->mlx, data->image->img);
	mlx_destroy_window(data->mlx, data->win);
	free(data->image);
	mlx_destroy_display(data->mlx);
	free(data->mlx);
	free(data);
}
