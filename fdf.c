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
		mlx_clear_window(data->mlx, data->win);
		draw_grid(*data, data->grid);
		ft_printf("Key pressed: %d\n", key);
	}
	return (0);
}

static int	init_data(t_data *data, int width, int height)
{
	data->mlx = mlx_init();
	if (data->mlx == NULL)
	{
		print_error("Failed to initialize mlx\n");
		return (1);
	}
	data->win = mlx_new_window(data->mlx, width, height, "FDF");
	if (data->win == NULL)
	{
		print_error("Failed to create window\n");
		return (1);
	}
	data->height = height;
	data->width = width;
	data->perspective = 0;
	return (0);
}
	

int	main(int argc, char **argv)
{
	t_data	data;
	t_grid	*grid;

	if (argc != 2 || init_data(&data, 1000, 1000) == 1)
		return (1);
	grid = create_grid(argv[1]);
	data.grid = grid;
	mlx_key_hook(data.win, handle_key, &data);
	draw_grid(data, grid);
	mlx_loop(data.mlx);
	return (0);
}
