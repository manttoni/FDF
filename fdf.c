#include "fdf.h"

int	handle_key(int key, t_data *data)
{
	if (key == 65307)
	{
		mlx_destroy_window(data->mlx, data->win);
		exit(0);
	}
	return (0);
}
int	main(void)
{
	t_data	data;

	data.mlx = mlx_init();
	if (data.mlx == NULL)
	{
		print_error("Failed to initialize mlx\n");
		return (1);
	}
	data.win = mlx_new_window(data.mlx, 1000, 1000, "FDF");
	if (data.win == NULL)
	{
		print_error("Failed to create window\n");
		return (1);
	}
	mlx_key_hook(data.win, handle_key, &data);
	mlx_loop(data.mlx);
	return (0);
}
