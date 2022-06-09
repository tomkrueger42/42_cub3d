#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	draw_box(int x_pos, int y_pos)
{
	int		x_px;
	int		y_px;
	size_t	color;

	y_px = 0;
	while (y_px < get_map()->tile_size - 0)
	{
		x_px = 0;
		while (x_px < get_map()->tile_size - 0)
		{
			if (get_map()->data[y_pos][x_pos] == '1')
				color = 0x444444;
			else if (get_map()->data[y_pos][x_pos] == ' ')
				return ;
			else
				color = 0xbbbbbb;
			if ((y_px == 0 || x_px == 0) && color != 0xFF000000) // borders between tiles
				color = 0x0;
			my_mlx_pixel_put(&get_graphics()->image, (x_pos * get_map()->tile_size) + x_px,
				(y_pos * get_map()->tile_size) + y_px, color);
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
	while (y_pos < get_map()->len)
	{
		x_pos = 0;
		while (x_pos < get_map()->width)
			draw_box(x_pos++, y_pos);
		y_pos++;
	}
	render_player();
}
