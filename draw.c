#include "fdf.h"

static void	draw_line(t_data *data, int x0, int y0, int x1, int y1)
{
	int dx = abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	while (1)
	{
		if (y0 < data->size && x0 < data->size && y0 > 0 && x0 > 0)
			*(int *)(data->image->img_data + (y0 * data->image->size_line + x0 * (data->image->bits_per_pixel / 8))) = 0xFFFFFF;
    	if (x0 == x1 && y0 == y1)
			break;
    	e2 = 2 * err;
    	if (e2 >= dy) 
		{
			err += dy;
			x0 += sx;
		}
    	if (e2 <= dx) 
		{ 
			err += dx; 
			y0 += sy; 
		}
	}
}

static void	draw_coords(t_data *data, t_grid *grid, t_coord start, t_coord end)
{
	int	dp;
	int	line_len;
	int	size;

	size = max(grid->width, grid->height);
	line_len = data->size / (size + 1);
	dp = line_len / 8;
	start.x = (start.x + (size - grid->width) / 2 + 1) * line_len;
	start.y = (start.y + (size - grid->height) / 2 + 1) * line_len; 
	end.x = (end.x + (size - grid->width) / 2 + 1) * line_len;
	end.y = (end.y + (size - grid->height) / 2 + 1) * line_len;
	rotate(data, &start);
	rotate(data, &end);
	draw_line(data, 
				start.x, 
				start.y - start.z * dp, 
				end.x, 
				end.y - end.z * dp);
}

void	draw_grid(t_data *data)
{
	int	x;
	int	y;
	t_coord	start;

	y = 0;
	while (y < data->grid->height)
	{
		x = 0;
		while (x < data->grid->width)
		{
			start = data->grid->coordinates[y][x];
			if (x + 1 < data->grid->width)
				draw_coords(data, data->grid, start, data->grid->coordinates[y][x + 1]);
			if (y + 1 < data->grid->height)
				draw_coords(data, data->grid, start, data->grid->coordinates[y + 1][x]);
			x++;
		}
		y++;
	}

}

