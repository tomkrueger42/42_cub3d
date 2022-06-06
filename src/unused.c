#include "cub3d.h"


// draws a box
void	highlight(int x, int y, int size, int color)
{
	int	x_step;
	int	y_step;

	y_step = - (size / 2);
	while (y_step <= size / 2)
	{
		x_step = - (size / 2);
		while (x_step <= size / 2)
		{
			my_mlx_pixel_put(get_graphics(), x + x_step, y + y_step, color);
			x_step++;
		}
		y_step++;
	}
}

void	draw_fov(double angle, double distance)
{
	double	x;
	double	y;
	double	xy;

	x = round(cos(angle) * distance * get_map()->tile_size);
	y = round(sin(angle) * distance * get_map()->tile_size);
	if (y == 0)
		xy = __INT_FAST64_MAX__;
	else
		xy = x / y;
	while (x != 0 || y != 0)
	{
		my_mlx_pixel_put(get_graphics(), get_player()->x_pos * get_map()->tile_size + x, get_player()->y_pos * get_map()->tile_size + y, 0xFFAA33);
		if (x > 0 && (y == 0 || (x / y >= xy && xy > 0) || (x / y < xy && xy < 0)))
			x--;
		else if (x < 0 && (y == 0 || (x / y <= xy && xy < 0) || (x / y > xy && xy > 0)))
			x++;
		else if (y > 0)
			y--;
		else if (y < 0)
			y++;
	}
}
