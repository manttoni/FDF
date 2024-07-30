#include "fdf.h"

int	max(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

double	convert_rad(double angle)
{
	//while (angle > 360)
	//	angle -= 360;
	return (angle * (M_PI / 180));
}

#include <stdio.h>

void	rotate(t_data data, t_coord *coord)
{
	double	angle;
	double	len;
	t_coord	origo;

	origo.x = data.width / 2;
	origo.y = data.height / 2;
	angle = atan2(0, 1) - atan2(coord->y - origo.y, coord->x - origo.x) + convert_rad(data.perspective);
	len = sqrt(pow(coord->x - origo.x, 2) + pow(coord->y - origo.y, 2));
	coord->x = (int) (len * cos(angle)) + origo.x;
	coord->y = (int) (len * sin(angle)) + origo.y;
}
