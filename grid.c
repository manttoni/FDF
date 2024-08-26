/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:16 by amaula            #+#    #+#             */
/*   Updated: 2024/08/26 13:22:51 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_len(char *line)
{
	int	len;

	len = 0;
	while (*line)
	{
		while (*line && *line == ' ')
			line++;
		if (*line)
			len++;
		while (*line && *line != ' ')
			line++;
	}
	return (len);
}

static void	set_dimensions(t_grid *grid, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	grid->width = count_len(line);
	grid->height = 0;
	grid->depth = 0;
	while (line)
	{
		free(line);
		grid->height++;
		line = get_next_line(fd);
	}
	close(fd);
}

static void	set_coord_values(t_grid *grid, int x, int y, int z)
{
	grid->coords[y][x].z = z;
	grid->coords[y][x].y = y;
	grid->coords[y][x].x = x;
}

static void	set_coords(t_grid *grid, char *file)
{
	char	**row_values;
	char	*line;
	int		fd;
	int		x;
	int		y;

	fd = open(file, O_RDONLY);
	y = 0;
	while (y < grid->height)
	{
		x = 0;
		line = get_next_line(fd);
		row_values = ft_split(line, ' ');
		while (x < grid->width)
		{
			set_coord_values(grid, x, y, ft_atoi(row_values[x]));
			grid->depth = max(grid->depth, ft_atoi(row_values[x]));
			free(row_values[x]);
			x++;
		}
		free(row_values);
		free(line);
		y++;
	}
	close(fd);
}

t_grid	*create_grid(char *file)
{
	t_grid	*grid;
	int		i;

	grid = malloc(sizeof(t_grid));
	if (grid == NULL)
		return (NULL);
	set_dimensions(grid, file);
	grid->coords = malloc(grid->height * sizeof(t_coord *));
	i = 0;
	while (i < grid->height)
	{
		grid->coords[i] = malloc(grid->width * sizeof(t_coord));
		i++;
	}
	set_coords(grid, file);
	return (grid);
}
