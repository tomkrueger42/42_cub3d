#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	draw_box(int x_pos, int y_pos)
{
	int		x_px;
	int		y_px;
	size_t	color;

	y_px = 0;
	while (y_px < map()->box_size - 0)
	{
		x_px = 0;
		while (x_px < map()->box_size - 0)
		{
			if (map()->data[y_pos][x_pos] == '1')
				color = 0x00444444;
			else if (map()->data[y_pos][x_pos] == ' ')
				color = 0xFF000000;
			else
				color = 0x00bbbbbb;
			if ((y_px == 0 || x_px == 0) && 0xFF000000 != color) // borders between tiles
				color = 0x0;
			my_mlx_pixel_put(graphics(), (x_pos * map()->box_size) + x_px,
				(y_pos * map()->box_size) + y_px, color);
			x_px++;
		}
		y_px++;
	}
}

void	render_minimap(void)
{
	int	x_pos;
	int	y_pos;

	y_pos = 0;
	while (y_pos < map()->len)
	{
		x_pos = 0;
		while (x_pos < map()->width)
			draw_box(x_pos++, y_pos);
		y_pos++;
	}
	render_player();
}
