/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:16 by amaula            #+#    #+#             */
/*   Updated: 2024/08/27 12:10:30 by amaula           ###   ########.fr       */
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


static void	set_coord_values(t_grid *grid, int x, int y, int z)
{
	grid->coords[y][x].z = z;
	grid->depth = max(grid->depth, abs(z));
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
			set_coord_values(grid, x++, grid->height - 1, ft_atoi(ptr));
			ptr = ft_strchr(ptr, ' ');
			if (ptr == NULL)
				break ;
			while (*ptr == ' ')
				ptr++;
		}
		free(line);
		line = get_next_line(fd);
	}
}

t_grid	*create_grid(char *file)
{
	t_grid	*grid;

	grid = malloc(sizeof(t_grid));
	if (grid == NULL)
		return (NULL);
	grid->coords = NULL;
	grid->depth = 0;
	grid->height = 0;
	parse_file(file, grid);
	return (grid);
}
