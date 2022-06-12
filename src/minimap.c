#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	draw_box(int x_pos, int y_pos, t_map *map)
{
	int		x_px;
	int		y_px;
	size_t	color;

	y_px = 0;
	while (y_px < map->tile_size - 0)
	{
		x_px = 0;
		while (x_px < map->tile_size - 0)
		{
			if (map->data[y_pos][x_pos] == '1')
				color = DARK_GREY;
			else if (map->data[y_pos][x_pos] == ' ')
				return ;
			else
				color = LIGHT_GREY;
			if (y_px == 0 || x_px == 0) // borders between tiles
				color = BLACK;
			mlx_put_pixel(get_graphics()->image, (x_pos * map->tile_size) + x_px,
				(y_pos * map->tile_size) + y_px, color);
			x_px++;
		}
		y_px++;
	}
}

void	render_minimap(void)
{
	int		x_pos;
	int		y_pos;
	t_map	*map;

	y_pos = 0;
	map = get_map();
	while (y_pos < map->len)
	{
		x_pos = 0;
		while (x_pos < map->width)
			draw_box(x_pos++, y_pos, map);
		y_pos++;
	}
	render_player();
}
