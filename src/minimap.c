#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	draw_box(int x_pos, int y_pos)
{
	int	x_px;
	int	y_px;
	int	color;

	y_px = 0;
	while (y_px < map()->box_size - 0)
	{
		x_px = 0;
		while (x_px < map()->box_size - 0)
		{
			if (map()->data[y_pos][x_pos] == '1')
				color = 0x00444444;
			else if (map()->data[y_pos][x_pos] == ' ')
				color = 0x000000;
			else
				color = 0x00bbbbbb;
			if (y_px == 0 || y_px == map()->box_size - 1 || x_px == 0 || x_px == map()->box_size -1)
				color = 0x0;
			my_mlx_pixel_put(&map()->minimap, (x_pos * map()->box_size) + x_px,
				(y_pos * map()->box_size) + y_px, color);
			x_px++;
		}
		y_px++;
	}
}

void	render_minimap(t_vars *vars)
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
	render_player(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	if (keycode == ESC_KEY)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == W_KEY || keycode == A_KEY || keycode == S_KEY || keycode == D_KEY
				|| keycode == ARROW_LEFT_KEY || keycode == ARROW_RIGHT_KEY)
	{
		move_player(keycode);
		render_minimap(vars);
	}
	return (0);
}

t_map	*map(void)
{
	static t_map	*map;

	if (map == NULL)
	{
		map = ft_calloc(1, sizeof(t_map));
		if (map == NULL)
			put_error_and_exit("malloc failure in map()", 1);
	}
	return (map);
}
