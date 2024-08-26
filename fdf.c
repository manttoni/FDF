#include "fdf.h"

int	handle_key(int key, t_data *data)
{
	if (key == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	if (key == 65363 || key == 65361)
	{
		if (key == 65363)
			data->perspective += 10;
		else
			data->perspective--;
		//mlx_clear_window(data->mlx, data->win);
		ft_memset(data->image->img_data, 0, data->size * data->size * 4);
		draw_grid(data);
		mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	}
	return (0);
}

static int	init_data(t_data *data, int size)
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
	

int	main(int argc, char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (data == NULL)
		return (1);
	if (argc != 2 || init_data(data, 1500) == 1)
		return (1);
	data->grid = create_grid(argv[1]);
	mlx_key_hook(data->win, handle_key, data);
	draw_grid(data);
	mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	mlx_loop(data->mlx);
	return (0);
}
