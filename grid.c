#include "fdf.h"

static void	set_dimensions(t_grid *grid, char *file)
{
	char	*line;
	int		fd;

	fd = open(file, O_RDONLY);
	line = get_next_line(fd);
	grid->width = ft_countchar(line, ' ') + 1;
	grid->height = 0;
	while (line)
	{
		free(line);
		grid->height++;
		line = get_next_line(fd);
	}
	close(fd);
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
			grid->coordinates[y][x].z = ft_atoi(row_values[x]);
			grid->coordinates[y][x].y = y;
			grid->coordinates[y][x].x = x;
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
	set_dimensions(grid, file);
	grid->coordinates = malloc(grid->height * sizeof(t_coord*));
	i = 0;
	while (i < grid->height)
	{
		grid->coordinates[i] = malloc(grid->width * sizeof(t_coord));
		i++;
	}
	set_coords(grid, file);
	return (grid);
}
