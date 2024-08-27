/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 12:45:11 by amaula            #+#    #+#             */
/*   Updated: 2024/08/27 13:31:10 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

typedef struct s_bresenham
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;
}	t_bresenham;

static t_bresenham	*init_bresenham(t_data *data, t_coord start, t_coord end)
{
	t_bresenham	*b;

	b = malloc(sizeof(t_bresenham));
	if (b == NULL)
	{
		free_data(data);
		exit(1);
	}
	b->dx = abs(end.x - start.x);
	if (start.x < end.x)
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

static void	color_pixel(t_data *data, t_coord pixel, int color)
{
	int	pixel_index;

	pixel_index = pixel.y * data->image->sl + pixel.x * (data->image->bpp / 8);
	if (pixel.x < data->size && pixel.x > 0)
		if (pixel.y < data->size && pixel.y > 0)
			*(int *)(data->image->img_data + pixel_index) = color;
}

void	swap(t_coord *a, t_coord *b)
{
	t_coord	tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
}

static void	draw_line(t_data *data, t_coord start, t_coord end)
{
	t_bresenham	*b;
	int			len;

	if (start.z > end.z)
		swap(&start, &end);
	if (!is_visible(data->size, start) && !is_visible(data->size, end))
		return ;
	len = hypot(abs(start.x - end.x), abs(start.y - end.y));
	b = init_bresenham(data, start, end);
	while (1)
	{
		color_pixel(data, start, get_colour(data->grid, start, end, len));
		if (start.x == end.x && start.y == end.y)
			break ;
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
	free(b);
}

static void	draw_coords(t_data *data, t_grid *grid, t_coord start, t_coord end)
{
	int	dp;
	int	line_len;
	int	size;

	size = max(grid->width, grid->height);
	line_len = data->size / size + data->zoom * size;
	dp = line_len / 10;
	start.x = (start.x + (size - grid->width) / 2 + 1) * line_len;
	start.y = (start.y + (size - grid->height) / 2 + 1) * line_len;
	end.x = (end.x + (size - grid->width) / 2 + 1) * line_len;
	end.y = (end.y +  (size - grid->height) / 2 + 1) * line_len;
	rotate(data, &start);
	rotate(data, &end);
	start.x += data->camera.x * 10;
	start.y += data->camera.y * 10;
	end.x += data->camera.x * 10;
	end.y += data->camera.y * 10;
	start.y -= start.z * dp;
	end.y -= end.z * dp;
	draw_line(data, start, end);
}

void	draw_grid(t_data *data)
{
	int		x;
	int		y;
	t_coord	start;
	t_coord	end;

	y = 0;
	while (y < data->grid->height)
	{
		x = 0;
		while (x < data->grid->width)
		{
			start = data->grid->coords[y][x];
			if (x + 1 < data->grid->width)
			{
				end = data->grid->coords[y][x + 1];
				draw_coords(data, data->grid, start, end);
			}
			if (y + 1 < data->grid->height)
				end = data->grid->coords[y + 1][x];
			if (y + 1 < data->grid->height)
				draw_coords(data, data->grid, start, end);
			x++;
		}
		y++;
	}
}
