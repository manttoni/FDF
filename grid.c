/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:16 by amaula            #+#    #+#             */
/*   Updated: 2024/08/27 12:19:12 by amaula           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int	count_width(char *line)
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

static t_coord	**ft_realloc(t_coord **old_ptr, size_t old_size)
{
	t_coord	**new_ptr;
	size_t	i;

	new_ptr = malloc((old_size + 1) * sizeof(t_coord *));
	if (new_ptr == NULL)
		return (NULL);
	i = 0;
	while (i < old_size)
	{
		new_ptr[i] = old_ptr[i];
		i++;
	}
	free(old_ptr);
	return (new_ptr);
}


static void	set_coord_values(t_grid *grid, int x, int y, char *ptr)
{
	int	z;
	char	*color;
	int	c;

	grid->coords[y][x].color = 0xFFFFFF;
	if (ft_strchr(ptr, ','))
	{
		grid->default_colors = 0;
		color = ft_substr(ptr, ft_strchr(ptr, ',') + 1 - ptr, ft_strchr(ptr, ' ') - 1 - ptr);
		c = hex_parser(color);
		if (c != -1)
			grid->coords[y][x].color = c;
		free(color);
	}
	z = ft_atoi(ptr);
	grid->coords[y][x].z = z;
	grid->max_depth = max(grid->max_depth, z);
	grid->min_depth = min(grid->min_depth, z);
	grid->coords[y][x].y = y;
	grid->coords[y][x].x = x;
}

static void	parse_file(char *file, t_grid *grid)
{
	int		fd;
	char	*line;
	char	*ptr;
	int		x;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	grid->width = count_width(line);
	while (line)
	{
		grid->coords = ft_realloc(grid->coords, grid->height++);
		ptr = line;
		x = 0;
		grid->coords[grid->height - 1] = malloc(grid->width * sizeof(t_coord));
		while (x < grid->width)
		{
			set_coord_values(grid, x++, grid->height - 1, ptr);
			ptr = ft_strchr(ptr, ' ');
			if (ptr == NULL)
				break ;
			while (*ptr == ' ')
				ptr++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

t_grid	*create_grid(char *file)
{
	t_grid	*grid;

	grid = malloc(sizeof(t_grid));
	if (grid == NULL)
		return (NULL);
	grid->coords = NULL;
	grid->max_depth = 0;
	grid->min_depth = 0;
	grid->height = 0;
	grid->default_colors = 1;
	parse_file(file, grid);
	if (grid->default_colors == 1)
		set_colors(grid);
	return (grid);
}
