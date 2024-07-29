#include "fdf.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	if (argc != 2)
		return 0;
	char *file = argv[1];
	t_grid *grid = create_grid(file);
	for (int i = 0; i < grid->height; i++)
	{
		for (int j = 0; j < grid->width; j++)
			ft_printf("%d ", grid->coordinates[i][j].z);
		ft_printf("\n");
	}
	return 0;
}
