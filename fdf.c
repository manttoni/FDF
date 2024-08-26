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
		draw_grid(*data, data->grid);
		mlx_put_image_to_window(data->mlx, data->win, data->image->img, 0, 0);
	}
	return (0);
}

static int	init_data(t_data *data, int size)
{
	t_image	*image;

	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		print_error("Failed to initialize mlx\n");
		return (1);
	}
	data->win = mlx_new_window(data->mlx, size, size, "FDF");
	if (data->win == NULL)
	{
		print_error("Failed to create window\n");
		return (1);
	}
	image = malloc(sizeof(t_image));
	image->img = mlx_new_image(data->mlx, size, size);
	image->img_data = mlx_get_data_addr(image->img, &(image->bits_per_pixel), &(image->size_line), &(image->endian));
	data->image = image;
	data->size = size;
	data->perspective = 0;
	return (0);
}
	

int	main(int argc, char **argv)
{
	t_data	data;
	t_grid	*grid;

	if (argc != 2 || init_data(&data, 1500) == 1)
		return (1);
	grid = create_grid(argv[1]);
	data.grid = grid;
	mlx_key_hook(data.win, handle_key, &data);
	draw_grid(data, grid);
	mlx_put_image_to_window(data.mlx, data.win, data.image->img, 0, 0);
	mlx_loop(data.mlx);
	return (0);
}
