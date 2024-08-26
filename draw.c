#include "fdf.h"

/*static void	draw_line2(t_data *data, t_coord start, t_coord end)
{
	int	dx;
	int dy;
	int	pixels;
	int	x;
	int	y;

	dx = end.x - start.x;
	dy = end.y - start.y;
	pixels = hypot(dx, dy);
	dx /= pixels;
	dy /= pixels;
	x = start.x;
	y = start.y;
	while (pixels)
	{
		*(int *)(data->image->img_data + (y * data->image->size_line + x * (data->image->bits_per_pixel / 8))) = 0xFFFFFF;
		x += dx;
		y += dy;
		--pixels;
	}
}*/
typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bresenham;

static t_bresenham	*init_bresenham(t_coord start, t_coord end)
{
	t_bresenham *b;

	b = malloc(sizeof(t_bresenham));
	b->dx = abs(end.x - start.x);
	if(start.x < end.x)
		b->sx = 1;
	else
		b->sx = -1;
	b->dy = -abs(end.y - start.y);
	if (start.y < end.y)
		b->sy = 1;
	else
		b->sy = -1;
	b->err = b->dx + b->dy;
	return (b);
}

static void	draw_line(t_data *data, t_coord start, t_coord end)
{
	t_bresenham *b;

	b = init_bresenham(start, end);
	while (1)
	{
		if (start.y < data->size && start.x < data->size && start.y > 0 && start.x > 0)
			*(int *)(data->image->img_data + (start.y * data->image->size_line + start.x * (data->image->bits_per_pixel / 8))) = 0xFFFFFF;
    	if (start.x == end.x && start.y == end.y)
			break;
    	b->e2 = 2 * b->err;
    	if (b->e2 >= b->dy) 
		{
			b->err += b->dy;
			start.x += b->sx;
		}
    	if (b->e2 <= b->dx) 
		{ 
			b->err += b->dx; 
			start.y += b->sy; 
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
	start.y -= start.z * dp;
	end.y -= end.z * dp;
	draw_line(data, start, end);
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

