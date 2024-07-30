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

void	draw_grid(t_data data, t_grid *grid)
{
	int	i;
	int	j;
	int	start_x = 0;
	int	start_y = 0;
	int	end_x = 0;
	//int	end_y = 0;
	
	j = 0;
	while (j < grid->height)
	{
		i = 0;
		start_x = 0;
		end_x = 0;
		start_y += data.height / (grid->height + 1);
		while (i < grid->width)
		{
			start_x += data.width / (grid->width + 1);
			end_x = start_x + data.width / (grid->width + 1);
			if (i < grid->width - 1)
				draw_line(data, start_x, start_y, end_x, start_y);
			if (j < grid->height - 1)
				draw_line(data, start_x, start_y, start_x, start_y + data.height / grid->height);
			i++;
		}
		j++;
	}
}
