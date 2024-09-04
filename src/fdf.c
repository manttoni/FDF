/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 11:57:24 by amaula            #+#    #+#             */
/*   Updated: 2024/09/04 12:29:33 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	handle_close(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	free_data(data);
	exit(0);
}

static void	redraw(t_data *data)
{
	ft_memset(data->image->img_data, 0, data->size * data->size * 4);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
}

int	handle_key(int key, t_data *data)
{
	if (key == ESCAPE_KEY)
	{
		free_data(data);
		exit(0);
	}
	if (key == LEFT_ARROW || key == RIGHT_ARROW)
		change_perspective(data, key);
	if (key == UP_ARROW || key == DOWN_ARROW)
		change_zoom(data, key);
	if (key == W || key == A || key == S || key == D)
		move_camera(data, key);
	if (key == DELETE)
		reset_all(data);
	redraw(data);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	ft_memset(data, 0, sizeof(t_data));
	if (data == NULL || argc != 2)
		return (1);
	data->grid = create_grid(argv[1]);
	if (data->grid == NULL || init_data(data, 1500) == 1)
	{
		free_data(data);
		return (1);
	}
	mlx_key_hook(data->win, handle_key, data);
	mlx_hook(data->win, 17, 0, handle_close, data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
