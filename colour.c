#include "fdf.h"

int	hex_parser(char *hex)
{
	int		res;
	const char	*chars;

	chars = "0123456789ABCDEF";
	if (hex[0] != '0' || hex[1] != 'x')
	{
		ft_printf("Not hex!\n");
		exit(1);
	}
	hex += 2;
	res = 0;
	while (ft_strchr(chars, ft_toupper(*hex)))
	{
		res *= 16;
		res += ft_strchr(chars, ft_toupper(*hex)) - chars;
		hex++;
	}
	return (res);
}

void	set_colours(t_grid *grid)
{
	int	y;
	int	x;
	t_coord *c;
	int	colour_change;

	y = 0;
	while (y < grid->height)
	{
		x = 0;
		while (x < grid->width)
		{
			c = &grid->coords[y][x];
			if (c->z < 0)
			{
				colour_change = 255 - 255 * c->z / grid->min_depth;
				c->colour = 255 << 16 | colour_change << 8 | colour_change;
			}
			else
			{
				colour_change = 255 - 255 * c->z / grid->max_depth;
				c->colour = colour_change << 16 | colour_change << 8 | 255;
			}
			x++;
		}
		y++;
	}
}
static void	break_down(t_colour *colour, int code)
{
	colour->r = (code >> 16) & 0xFF;
	colour->g = (code >> 8) & 0xFF;
	colour->b = code & 0xFF;
}
/*start is where the line started, but its x and y are probably changed
 * its z and colour are not*/
int     get_colour(t_coord start, t_coord end, int len)
{
        double		t;
	t_colour	start_colour;
	t_colour	end_colour;
	t_colour	pixel_colour;

        if (len == 0)
                return (start.colour);
	break_down(&start_colour, start.colour);
	break_down(&end_colour, end.colour);
        t = 1 - hypot(abs(start.x - end.x), abs(start.y - end.y)) / (double)len;
	pixel_colour.r = (int)(start_colour.r + (end_colour.r - start_colour.r) * t);
	pixel_colour.g = (int)(start_colour.g + (end_colour.g - start_colour.g) * t);
	pixel_colour.b = (int)(start_colour.b + (end_colour.b - start_colour.b) * t);
	if (pixel_colour.r > 255) pixel_colour.r = 255;
	if (pixel_colour.g > 255) pixel_colour.g = 255;
	if (pixel_colour.b > 255) pixel_colour.b = 255;
	if (pixel_colour.r < 0) pixel_colour.r = 0;
	if (pixel_colour.g < 0) pixel_colour.g = 0;
		if (pixel_colour.b < 0) pixel_colour.b = 0;
        return (pixel_colour.r << 16 | pixel_colour.g << 8 | pixel_colour.b);
}
