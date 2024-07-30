#include "fdf.h"

static void	draw_line(t_data data, int x0, int y0, int x1, int y1)
{
	int dx =  abs (x1 - x0), sx = x0 < x1 ? 1 : -1;
	int dy = -abs (y1 - y0), sy = y0 < y1 ? 1 : -1;
	int err = dx + dy, e2; /* error value e_xy */

	while (1)
	{
    	mlx_pixel_put(data.mlx, data.win, x0, y0, 0xFFFFFFFF);
    	if (x0 == x1 && y0 == y1) break;
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

static void	draw_coords(t_data data, t_grid *grid, t_coord start, t_coord end)
{
	int	hz;
	int	vc;
	int	dp;

	hz = data.width / (grid->width + 1);
	vc = data.height / (grid->height + 1);
	dp = vc / 4;
	draw_line(data, (start.x + 1) * hz, (start.y + 1) * vc - start.z * dp, (end.x + 1) * hz, (end.y + 1) * vc - end.z * dp);
}

void	draw_grid(t_data data, t_grid *grid)
{
	int	x;
	int	y;
	t_coord	start;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			start = grid->coordinates[y][x];
			if (x + 1 < grid->width)
				draw_coords(data, grid, start, grid->coordinates[y][x + 1]);
			if (y + 1 < grid->height)
				draw_coords(data, grid, start, grid->coordinates[y + 1][x]);
			x++;
		}
		y++;
	}
}

