#include <stdio.h>
#include "../inc/cub3d.h"
#include <stdlib.h>

void make_map(t_vars vars)
{
	map()->data = ft_calloc(10, sizeof(char *));
	map()->data[0] = ft_strdup("1111111");
	map()->data[1] = ft_strdup("1 01001");
	map()->data[2] = ft_strdup("1001101");
	map()->data[3] = ft_strdup("11 1 00");
	map()->data[4] = ft_strdup("1111111");
	map()->data[5] = ft_strdup("       ");
	map()->data[6] = ft_strdup("0000000");
	map()->data[7] = ft_strdup("0001010");
	map()->data[8] = ft_strdup("1110101");
	map()->data[9] = NULL;
	map()->width = 7;
	map()->len = 9;
	if (map()->width > map()->len)
		map()->box_size = MAPWIN / map()->width;
	else
		map()->box_size = MAPWIN / map()->len;
	map()->minimap = ft_calloc(1, sizeof(t_img));
	if (map()->minimap == NULL)
		put_error_and_exit("malloc failure in make_map()", 1);
	map()->minimap->img = mlx_new_image(vars.mlx, MAPWIN, MAPWIN);
	map()->minimap->addr = mlx_get_data_addr(map()->minimap->img,
		&map()->minimap->bits_per_pixel, &map()->minimap->line_length,
		&map()->minimap->endian);
}

void	draw_box(int x_pos, int y_pos)
{
	int	x_px;
	int	y_px;
	int	color;

	y_px = /* 1 */ 0;
	while (y_px < map()->box_size - /* 1 */ 0)
	{
		x_px = /* 1 */ 0;
		while (x_px < map()->box_size - /* 1 */ 0)
		{
			if (map()->data[y_pos][x_pos] == '1')								// wall
				color = 0x00444444;
			else if (map()->data[y_pos][x_pos] == ' ')							// black, should later be transparent
				color = 0x000000;
			else
				color = 0x00bbbbbb;												// ground below player / sprite
			if (y_px == 0 || y_px == map()->box_size - 1 || x_px == 0 || x_px == map()->box_size -1)
				color = 0x0;
			my_mlx_pixel_put(map()->minimap, (x_pos * map()->box_size) + x_px,
				(y_pos * map()->box_size) + y_px, color);
			x_px++;
		}
		y_px++;
	}
}

void	render_minimap(t_vars *vars)
{
	static int	asdf = 0;
	int	x_pos;
	int	y_pos;

	if (asdf == 0)
	{
		y_pos = 0;
		while (y_pos < map()->len)
		{
			x_pos = 0;
			while (x_pos < map()->width)
				draw_box(x_pos++, y_pos);
			y_pos++;
		}
		asdf = 1;
	}
	render_player(vars);
}

int	key_hook(int keycode, t_vars *vars)
{
	// printf("keyhook: %i\n", keycode);
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(0);
	}
	else if (keycode == 13 || keycode == 0 || keycode == 1 || keycode == 2 || keycode == 123 || keycode == 124)
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

int	main(void)
{
	t_vars	vars;

	vars.mlx = mlx_init();
	make_map(vars);
	vars.win = mlx_new_window(vars.mlx, map()->width * map()->box_size, map()->len * map()->box_size, "cub3d minimap");
	render_minimap(&vars);
	mlx_hook(vars.win, 02, 1L<<0, key_hook, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
