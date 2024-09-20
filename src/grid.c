/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grid.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaula <amaula@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/26 13:19:16 by amaula            #+#    #+#             */
/*   Updated: 2024/09/20 15:47:10 by amaula           ###   ########.fr       */
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

/*sr = strchr result with ',' to make it short for norminette
  sv = set coordinate values for same reason*/
static void	sv(t_grid *grid, int x, int y, char *ptr)
{
	int		z;
	char	*color;
	int		c;
	char	*sr;

	grid->coords[y][x].color = 0xFFFFFF;
	sr = ft_strchr(ptr, ',');
	if (sr)
	{
		grid->default_colors = 0;
		color = ft_substr(ptr, sr + 1 - ptr, ft_strchr(ptr, ' ') - 1 - ptr);
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

int	parse_file(t_file_reader file_reader, t_grid *grid)
{
	grid->width = count_width(file_reader.line);
	while (file_reader.line)
	{
		grid->coords = ft_realloc(grid->coords, grid->height++);
		file_reader.ptr = file_reader.line;
		file_reader.x = 0;
		grid->coords[grid->height - 1] = malloc(grid->width * sizeof(t_coord));
		while (file_reader.x < grid->width)
		{
			sv(grid, file_reader.x++, grid->height - 1, file_reader.ptr);
			file_reader.ptr = ft_strchr(file_reader.ptr, ' ');
			if (file_reader.ptr == NULL)
				break ;
			while (*(file_reader.ptr) == ' ')
				file_reader.ptr++;
		}
		free(file_reader.line);
		file_reader.line = get_next_line(file_reader.fd);
	}
	close(file_reader.fd);
	return (1);
}

t_grid	*create_grid(char *file)
{
	t_grid			*grid;
	t_file_reader	file_reader;

	grid = malloc(sizeof(t_grid));
	if (grid == NULL)
		return (NULL);
	ft_memset(grid, 0, sizeof(t_grid));
	grid->default_colors = 1;
	file_reader.fd = open(file, O_RDONLY);
	file_reader.line = get_next_line(file_reader.fd);
	if (file_reader.line == NULL)
	{
		ft_printf("File is empty.\n");
		free(file_reader.line);
		close(file_reader.fd);
		free(grid);
		return (NULL);
	}
	if (parse_file(file_reader, grid) == 0)
	{
		free(grid);
		return (NULL);
	}
	if (grid->default_colors == 1)
		set_colors(grid);
	return (grid);
}
